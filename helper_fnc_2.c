#include "shell.h"

void line_handler(char **line, ssize_t read);
ssize_t new_length_getter(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
* line_handler - Partitions a line read from standard input as needed.
* @line: A pointer to a line read from standard input.
* @read: The length of line.
*
* Description: Spaces are inserted to separate ";", "||", and "&&".
*              Replaces "#" with '\0'.
*/
void line_handler(char **line, ssize_t read)
{
char *old_ln, *new_ln;
char prvs, current, next;
size_t i, j;
ssize_t new_len;

new_len = new_length_getter(*line);
if (new_len == read - 1)
return;
new_ln = malloc(new_len + 1);
if (!new_ln)
return;
j = 0;
old_ln = *line;
for (i = 0; old_ln[i]; i++)
{
current = old_ln[i];
next = old_ln[i + 1];
if (i != 0)
{
prvs = old_ln[i - 1];
if (current == ';')
{
if (next == ';' && prvs != ' ' && prvs != ';')
{
new_ln[j++] = ' ';
new_ln[j++] = ';';
continue;
}
else if (prvs == ';' && next != ' ')
{
new_ln[j++] = ';';
new_ln[j++] = ' ';
continue;
}
if (prvs != ' ')
new_ln[j++] = ' ';
new_ln[j++] = ';';
if (next != ' ')
new_ln[j++] = ' ';
continue;
}
else if (current == '&')
{
if (next == '&' && prvs != ' ')
new_ln[j++] = ' ';
else if (prvs == '&' && next != ' ')
{
new_ln[j++] = '&';
new_ln[j++] = ' ';
continue;
}
}
else if (current == '|')
{
if (next == '|' && prvs != ' ')
new_ln[j++] = ' ';
else if (prvs == '|' && next != ' ')
{
new_ln[j++] = '|';
new_ln[j++] = ' ';
continue;
}
}
}
else if (current == ';')
{
if (i != 0 && old_ln[i - 1] != ' ')
new_ln[j++] = ' ';
new_ln[j++] = ';';
if (next != ' ' && next != ';')
new_ln[j++] = ' ';
continue;
}
new_ln[j++] = old_ln[i];
}
new_ln[j] = '\0';

free(*line);
*line = new_ln;
}

/**
* new_length_getter - Gets the new length of a line partitioned
*               by ";", "||", "&&&", or "#".
* @line: The line to check.
*
* Return: The new length of the line.
*
* Description: Cuts short lines containing '#' comments with '\0'.
*/

ssize_t new_length_getter(char *line)
{
size_t i;
ssize_t new_len = 0;
char current, next;

for (i = 0; line[i]; i++)
{
current = line[i];
next = line[i + 1];
if (current == '#')
{
if (i == 0 || line[i - 1] == ' ')
{
line[i] = '\0';
break;
}
}
else if (i != 0)
{
if (current == ';')
{
if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
{
new_len += 2;
continue;
}
else if (line[i - 1] == ';' && next != ' ')
{
new_len += 2;
continue;
}
if (line[i - 1] != ' ')
new_len++;
if (next != ' ')
new_len++;
}
else
logical_ops(&line[i], &new_len);
}
else if (current == ';')
{
if (i != 0 && line[i - 1] != ' ')
new_len++;
if (next != ' ' && next != ';')
new_len++;
}
new_len++;
}
return (new_len);
}
/**
* logical_ops - Checks a line for logical operators "||" or "&&".
* @line: A pointer to the character to check in the line.
* @new_len: Pointer to new_len in new_length_getter function.
*/
void logical_ops(char *line, ssize_t *new_len)
{
char prvs, current, next;

prvs = *(line - 1);
current = *line;
next = *(line + 1);

if (current == '&')
{
if (next == '&' && prvs != ' ')
(*new_len)++;
else if (prvs == '&' && next != ' ')
(*new_len)++;
}
else if (current == '|')
{
if (next == '|' && prvs != ' ')
(*new_len)++;
else if (prvs == '|' && next != ' ')
(*new_len)++;
}
}
