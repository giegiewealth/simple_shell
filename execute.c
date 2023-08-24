#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - Execute a command.
 * @command: The command to be executed
 * This function takes a command string as input
 * and executes it using
 * the appropriate system call.
 * It parses the command and its arguments,
 * then attempts to execute it.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(const char *command)
{
char *token = strtok((char *)command, " ");
{
pid_t child_pid = fork();

if (child_pid == -1)
{
leo_print("Error forking process.\n");
exit(EXIT_FAILURE);
}
else if (child_pid == 0)
{
char *args[128];

int arg_count = 0;

execvp(args[0], args);
while (token != NULL)
{
args[arg_count++] = token;
token = strtok(NULL, " ");
}
args[arg_count] = NULL;

execvp(args[0], args);

leo_print("Error executing command.\n");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
return 0;
}
}
}
