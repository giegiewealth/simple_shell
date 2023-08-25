#include "shell.h"

char *path_dir_filler(char *path);
list_t *path_dir_getter(char *path);

/**
* get_location - Locates a command in the PATH.
* @command: The command to locate.
*
* Return: If an error occurs or the command cannot be located - NULL.
*         Otherwise - the full pathname of the command.
*/
char *get_location(char *command)
{
char **path, *temp;
list_t *dirs, *head;
struct stat st;

path = _getenv("PATH");
if (!path || !(*path))
return (NULL);

dirs = path_dir_getter(*path + 5);
head = dirs;

while (dirs)
{
temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
if (!temp)
return (NULL);

_strcpy(temp, dirs->dir);
_strcat(temp, "/");
_strcat(temp, command);

if (stat(temp, &st) == 0)
{
list_freer(head);
return (temp);
}

dirs = dirs->next;
free(temp);
}

list_freer(head);

return (NULL);
}

/**
* path_dir_filler - Copies path but also replaces leading/sandwiched/trailing
*		   colons (:) with current working directory.
* @path: The colon-separated list of directories.
*
* Return: A copy of path with any leading/sandwiched/trailing colons replaced
*	   with the current working directory.
*/
char *path_dir_filler(char *path)
{
int i, length = 0;
char *path_cp, *pwd;

pwd = *(_getenv("PWD")) + 4;
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
length += _strlen(pwd) + 1;
else
length++;
}
else
length++;
}
path_cp = malloc(sizeof(char) * (length + 1));
if (!path_cp)
return (NULL);
path_cp[0] = '\0';
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (i == 0)
{
_strcat(path_cp, pwd);
_strcat(path_cp, ":");
}
else if (path[i + 1] == ':' || path[i + 1] == '\0')
{
_strcat(path_cp, ":");
_strcat(path_cp, pwd);
}
else
_strcat(path_cp, ":");
}
else
{
_strncat(path_cp, &path[i], 1);
}
}
return (path_cp);
}

/**
* path_dir_getter - Tokenizes a colon-separated list of
*                directories into a list_str linked list.
* @path: The colon-separated list of directories.
*
* Return: A pointer to the initialized linked list.
*/
list_t *path_dir_getter(char *path)
{
int index;
char **dirs, *path_cp;
list_t *head = NULL;

path_cp = path_dir_filler(path);
if (!path_cp)
return (NULL);
dirs = _strtok(path_cp, ":");
free(path_cp);
if (!dirs)
return (NULL);

for (index = 0; dirs[index]; index++)
{
if (node_adder_end(&head, dirs[index]) == NULL)
{
list_freer(head);
free(dirs);
return (NULL);
}
}

free(dirs);

return (head);
}
