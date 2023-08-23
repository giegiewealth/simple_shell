#include "shell.h"

/**
<<<<<<< HEAD
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
=======
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
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af
}
