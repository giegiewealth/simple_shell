#include "shell.h"

/**
* _memset - fills memory with a constant byte.......
* @s: the pointer to the memory area.......
* @b: the byte to fill *s with.......
* @n: the amount of bytes to be filled.......
* Return: (s) a pointer to the memory area s.......
*/
char *_memset(char *s, char b, unsigned int n)
{
unsigned int index;

for (index = 0; index < n; index++)
s[index] = b;
return (s);
}

/**
* ffree - frees a string of strings....
* @pp: string of strings....
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
* _realloc - reallocates a block of memory......
* @ptr: pointer to previous malloc'ated block......
* @size_old: byte size of previous block......
* @size_new: byte size of new block......
*
* Return: pointer to da ol'block nameen.......
*/
void *_realloc(void *ptr, unsigned int size_old, unsigned int size_new)
{
char *p;

if (!ptr)
return (malloc(size_new));
if (!size_new)
return (free(ptr), NULL);
if (size_new == size_old)
return (ptr);

p = malloc(size_new);
if (!p)
return (NULL);

size_old = size_old < size_new ? size_old : size_new;
while (size_old--)
p[size_old] = ((char *)ptr)[size_old];
free(ptr);
return (p);
}
