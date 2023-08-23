#include "shell.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(info_t *info, char **av)
{
ssize_t r_index = 0;
int builtin_ret = 0;

while (r_index != -1 && builtin_ret != -2)
{
clear_info(info);
if (intrtv(info))
_puts("$ ");
eputcharsc(BUF_FLUSH);
r_index = get_input(info);
if (r_index != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (intrtv(info))
_putchar('\n');
free_info(info, 0);
}
wrt_hist(info);
free_info(info, 1);
if (!intrtv(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}

/**
* find_builtin - finds a builtin command......
* @info: the parameter & return info struct......
*
* Return: -1 if builtin not found,......
* 	0 if builtin executed successfully,......
* 	1 if builtin found but not successful,......
* 	2 if builtin signals exit()......
*/
int find_builtin(info_t *info)
{
int index, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _exitd},
{"env", _environd},
{"help", _helpd},
{"history", _hist},
{"setenv", _setenv},
{"ukwnenv", _myukwnenv},
{"cd", _chngd},
{"alias", _aliasd},
{NULL, NULL}};

for (index = 0; builtintbl[index].type; index++)
if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[index].func(info);
break;
}
return (built_in_ret);
}

/**
* find_cmd - finds a command in PATH....
* @info: the parameter & return info struct....
*
* Return: void....
*/
void find_cmd(info_t *info)
{
char *path = NULL;
int index, k_index;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (index = 0, k_index = 0; info->arg[index]; index++)
if (!is_delim(info->arg[index], " \t\n"))
k_index++;
if (!k_index)
return;

path = find_path(info, fetchenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((intrtv(info) || fetchenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
prnt_errmsg(info, "not found\n");
}
}
}

/**
* fork_cmd - forks a an exec thread to run cmd......
* @info: the parameter & return info struct......
*
* Return: void......
*/
void fork_cmd(info_t *info)
{
pid_t child_pID;

child_pID = fork();
if (child_pID == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pID == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
prnt_errmsg(info, "Permission Denied\n");
}
}
}
