#include "shell.h"

/**
* main - entry point
* @argc: arg count
* @agrv: arg vector
*
* Return: 0 on success, 1 on error
*/
int main(int argc, char **agrv)
{
info_t command[] = {INFO_INIT};
int fd = 2;
if (argc == 2)
{
fd = open(agrv[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
{

exit(126);
}
else if (errno == ENOENT)
{
_eputs(agrv[0]);
_eputs(": 0: Can't open ");
_eputs(agrv[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
else
{
perror("open");
exit(EXIT_FAILURE);
}
}
command.readfd = fd;
}
populate_env_list(command);
read_history(command);
hsh(command, agrv);
return (EXIT_SUCCESS);
}
