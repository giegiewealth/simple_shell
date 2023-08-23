#include "shell.h"

/**
* _exitd - exits the shell
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: exits with a given exit status
* (0) if info.argv[0] != "exit"
*/
int _exitd(info_t *info)
{
int exit_check;

if (info->argv[1]) /* If there is an exit argument */
{
exit_check = __errorcatoiatoi(info->argv[1]);
if (exit_check == -1)
{
info->status = 2;
prnt_errmsg(info, "Wrong number: ");
_eputs(info->argv[1]);
eputcharsc('\n');
return (1);
}
info->err_num = __errorcatoiatoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
* _chngd - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _chngd(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure e-msg here<<\n");
if (!info->argv[1])
{
dir = fetchenv(info, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = fetchenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!fetchenv(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(fetchenv(info, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = fetchenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
prnt_errmsg(info, "can't cd to ");
_eputs(info->argv[1]), eputcharsc('\n');
}
else
{
_setenv(info, "OLDPWD", fetchenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* _helpd - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _helpd(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("Help call works. Function is not yet implemented\n");
if (0)
_puts(*arg_array); /* temp att_unused workaround */
return (0);
}
