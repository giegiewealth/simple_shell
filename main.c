#include "shell.h"

void handlle_signal(int sig);
int execute(char **args, char **front);
int histry;
char *name;

/**
 * handlle_signal - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void handlle_signal(int sig)
{
	char *prmpt_new = "\n$ ";

	(void)sig;
	signal(SIGINT, handlle_signal);
	write(STDIN_FILENO, prmpt_new, 3);
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (print_error(args, 126));
		else
			ret = (print_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (print_error(args, 126));
			envmnt_freer();
			args_freer(args, front);
			alias_list_freer(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_ln = "\n";

	name = argv[0];
	histry = 1;
	aliases = NULL;
	signal(SIGINT, handlle_signal);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_comm(argv[1], exe_ret);
		envmnt_freer();
		alias_list_freer(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = args_handler(exe_ret);
		envmnt_freer();
		alias_list_freer(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = args_handler(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_ln, 1);
			envmnt_freer();
			alias_list_freer(aliases);
			exit(*exe_ret);
		}
	}

	envmnt_freer();
	alias_list_freer(aliases);
	return (*exe_ret);
}
