#include "shell.h"

void args_freer(char **args, char **front);
char *get_pid(void);
char *env_val_getter(char *beginning, int len);
void rplc_var(char **args, int *exe_ret);

/**
* args_freer - Frees up memory taken by args.
* @args: A null-terminated double pointer containing commands/arguments.
* @front: A double pointer to the beginning of args.
*/
void args_freer(char **args, char **front)
{
size_t i;

for (i = 0; args[i] || args[i + 1]; i++)
free(args[i]);

free(front);
}

/**
* get_pid - Gets the current process ID.
* Description: Opens the stat file, a space-delimited file containing
*              information about the current process. The PID is the
*              first word in the file. The function reads the PID into
*              a buffer and replace the space at the end with a \0 byte.
*
* Return: The current process ID or NULL on failure.
*/
char *get_pid(void)
{
size_t i = 0;
char *buffer;
ssize_t file;

file = open("/proc/self/stat", O_RDONLY);
if (file == -1)
{
perror("Cant read file");
return (NULL);
}
buffer = malloc(120);
if (!buffer)
{
close(file);
return (NULL);
}
read(file, buffer, 120);
while (buffer[i] != ' ')
i++;
buffer[i] = '\0';

close(file);
return (buffer);
}

/**
* env_val_getter - Gets the value corresponding to an environmental variable.
* @beginning: The environmental variable to search for.
* @len: The length of the environmental variable to search for.
*
* Return: If the variable is not found - an empty string.
*         Otherwise - the value of the environmental variable.
*
* Description: Variables are stored in the format VARIABLE=VALUE.
*/
char *env_val_getter(char *beginning, int len)
{
char **var_addr;
char *replacement = NULL, *temp, *var;

var = malloc(len + 1);
if (!var)
return (NULL);
var[0] = '\0';
_strncat(var, beginning, len);

var_addr = _getenv(var);
free(var);
if (var_addr)
{
temp = *var_addr;
while (*temp != '=')
temp++;
temp++;
replacement = malloc(_strlen(temp) + 1);
if (replacement)
_strcpy(replacement, temp);
}

return (replacement);
}

/**
* rplc_var - Handles variable replacement.
* @line: A double pointer containing the command and arguments.
* @exe_ret: A pointer to the return value of the last executed command.
*
* Description: Replaces $$ with the current PID, $? with the return value
*              of the last executed program, and environmental variables
*              preceded by $ with their corresponding value.
*/
void rplc_var(char **line, int *exe_ret)
{
int j, k = 0, len;
char *replacement = NULL, *old_ln = NULL, *new_ln;

old_ln = *line;
for (j = 0; old_ln[j]; j++)
{
if (old_ln[j] == '$' && old_ln[j + 1] &&
old_ln[j + 1] != ' ')
{
if (old_ln[j + 1] == '$')
{
replacement = get_pid();
k = j + 2;
}
else if (old_ln[j + 1] == '?')
{
replacement = _itoa(*exe_ret);
k = j + 2;
}
else if (old_ln[j + 1])
{
/* extract the variable name to search for */
for (k = j + 1; old_ln[k] &&
old_ln[k] != '$' &&
old_ln[k] != ' ';
k++)
;
len = k - (j + 1);
replacement = env_val_getter(&old_ln[j + 1], len);
}
new_ln = malloc(j + _strlen(replacement) + _strlen(&old_ln[k]) + 1);
if (!line)
return;
new_ln[0] = '\0';
_strncat(new_ln, old_ln, j);
if (replacement)
{
_strcat(new_ln, replacement);
free(replacement);
replacement = NULL;
}
_strcat(new_ln, &old_ln[k]);
free(old_ln);
*line = new_ln;
old_ln = new_ln;
j = -1;
}
}
}
