#include "shell.h"
int (*built_in_getter(char *command))(char **args, char **front);
int sh_exit(char **args, char **front);
int sh_cd(char **args, char __attribute__((__unused__)) **front);
int sh_help(char **args, char __attribute__((__unused__)) **front);

/**
* built_in_getter - Matches a command with a corresponding
*               sh builtin function.
* @command: The command to match.
*
* Return: A function pointer to the corresponding builtin.
*/
int (*built_in_getter(char *command))(char **args, char **front)
{
builtin_t funcs[] = {
{"exit", sh_exit},
{"env", sh_env},
{"setenv", sh_setenv},
{"unsetenv", sh_unsetenv},
{"cd", sh_cd},
{"alias", sh_alias},
{"help", sh_help},
{NULL, NULL}};
int i;

for (i = 0; funcs[i].name; i++)
{
if (_strcmp(funcs[i].name, command) == 0)
break;
}
return (funcs[i].f);
}

/**
* sh_exit - Causes normal process termination
*                for the sh shell.
* @args: An array of arguments containing the exit value.
* @front: A double pointer to the beginning of args.
*
* Return: If there are no arguments - -3.
*         If the given exit value is invalid - 2.
*         O/w - exits with the given status value.
*
* Description: Upon returning -3, the program exits back in the main function.
*/
int sh_exit(char **args, char **front)
{
int i, len_of_int = 10;
unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

if (args[0])
{
if (args[0][0] == '+')
{
i = 1;
len_of_int++;
}
else
i = 0;

for (; args[0][i]; i++)
{
if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
num = (num * 10) + (args[0][i] - '0');
else
return (print_error(--args, 2));
}
}
else
{
return (-3);
}
if (num > max - 1)
return (print_error(--args, 2));
args -= 1;
args_freer(args, front);
envmnt_freer();
alias_list_freer(aliases);
exit(num);
}

/**
* sh_cd - Changes the current directory of the sh process.
* @args: An array of arguments.
* @front: A double pointer to the beginning of args.
*
* Return: If the given string is not a directory - 2.
*         If an error occurs - -1.
*         Otherwise - 0.
*/
int sh_cd(char **args, char __attribute__((__unused__)) **front)
{
char **dir_info, *new_ln = "\n";
char *oldpwd = NULL, *pwd = NULL;
struct stat dir;

oldpwd = getcwd(oldpwd, 0);
if (!oldpwd)
return (-1);

if (args[0])
{
if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
{
if ((args[0][1] == '-' && args[0][2] == '\0') ||
args[0][1] == '\0')
{
if (_getenv("OLDPWD") != NULL)
(chdir(*_getenv("OLDPWD") + 7));
}
else
{
free(oldpwd);
return (print_error(args, 2));
}
}
else
{
if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
		&& ((dir.st_mode & S_IXUSR) != 0))
chdir(args[0]);
else
{
free(oldpwd);
return (print_error(args, 2));
}
}
}
else
{
if (_getenv("HOME") != NULL)
chdir(*(_getenv("HOME")) + 5);
}

pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);

dir_info = malloc(sizeof(char *) * 2);
if (!dir_info)
return (-1);

dir_info[0] = "OLDPWD";
dir_info[1] = oldpwd;
if (sh_setenv(dir_info, dir_info) == -1)
return (-1);

dir_info[0] = "PWD";
dir_info[1] = pwd;
if (sh_setenv(dir_info, dir_info) == -1)
return (-1);
if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, new_ln, 1);
}
free(oldpwd);
free(pwd);
free(dir_info);
return (0);
}

/**
* sh_help - Displays information about sh builtin commands.
* @args: An array of arguments.
* @front: A pointer to the beginning of args.
*
* Return: If an error occurs - -1.
*         Otherwise - 0.
*/
int sh_help(char **args, char __attribute__((__unused__)) **front)
{
if (!args[0])
all_helper();
else if (_strcmp(args[0], "alias") == 0)
alias_helper();
else if (_strcmp(args[0], "cd") == 0)
cd_helper();
else if (_strcmp(args[0], "exit") == 0)
exit_helper();
else if (_strcmp(args[0], "env") == 0)
envmnt_helper();
else if (_strcmp(args[0], "setenv") == 0)
set_envmnt_helper();
else if (_strcmp(args[0], "unsetenv") == 0)
unset_envmnt_helper();
else if (_strcmp(args[0], "help") == 0)
help_helper();
else
write(STDERR_FILENO, name, _strlen(name));

return (0);
}
