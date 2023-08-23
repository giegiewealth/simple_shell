
#include "shell.h"

/**
* chain_delimeter - test if current char in buffer
* is a chain delimeter...........
* @info: the parameter struct...........
* @buf: the char buffer...........
* @p: address of current position in buf...........
*
* Return: 1 if chain delimeter, 0 otherwise...........
*/

int chain_delimeter(info_t *info, char *buf, size_t *p)
{
size_t sizeJ = *p;

if (buf[sizeJ] == '|' && buf[sizeJ + 1] == '|')
{
buf[sizeJ] = 0;
sizeJ++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[sizeJ] == '&' && buf[sizeJ + 1] == '&')
{
buf[sizeJ] = 0;
sizeJ++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[sizeJ] == ';')
{
buf[sizeJ] = 0;
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = sizeJ;
return (1);
}

/**
* check_chain_delimeter - checks we should continue
* chaining based on last status
* @info: the parameter struct.........
* @buf: the char buffer.........
* @p: address of current position in buf.........
* @i: starting position in buf.........
* @len: length of buf.........
*
* Return: Void
*/
void check_chain_delimeter(info_t *info, char *buf,
size_t *p, size_t i, size_t len)
{
size_t sizeJ = *p;

if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
sizeJ = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
sizeJ = len;
}
}

*p = sizeJ;
}

/**
* replace_aliasToke - replaces an aliases in the tokenized string........
* @info: the parameter struct........
*
* Return: 1 if replaced, 0 otherwise......
*/
int replace_aliasToke(info_t *info)
{
int index;
list_t *node_lsit;
char *p;

for (index = 0; index < 10; index++)
{
node_lsit = node_starts_with(info->alias, info->argv[0], '=');
if (!node_lsit)
return (0);
free(info->argv[0]);
p = _strchr(node_lsit->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}

/**
* replace_varsToke - replaces vars in the tokenized string.....
* @info: the parameter struct.....
*
* Return: 1 if replaced, 0 otherwise.....
*/
int replace_varsToke(info_t *info)
{
int index = 0;
list_t *node;

for (index = 0; info->argv[index]; index++)
{
if (info->argv[index][0] != '$' || !info->argv[index][1])
continue;

if (!_strcmp(info->argv[index], "$?"))
{
replace_strings(&(info->argv[index]),
_strdup(convert_number(info->status, 10, 0)));
continue;
}
if (!_strcmp(info->argv[index], "$$"))
{
replace_strings(&(info->argv[index]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(info->env, &info->argv[index][1], '=');
if (node)
{
replace_strings(&(info->argv[index]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_strings(&info->argv[index], _strdup(""));
}
return (0);
}

/**
* replace_strings - replaces string....
* @old: address of old string....
* @new: new string....
*
* Return: 1 if replaced, 0 otherwise....
*/
int replace_strings(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
