#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_ln_ptr(char **ln_ptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **ln_ptr, size_t *n, FILE *stream);

/**
* _realloc - Reallocates a memory block using malloc and free.
* @ptr: A pointer to the memory previously allocated.
* @old_size: The size in bytes of the allocated space for ptr.
* @new_size: The size in bytes for the new memory block.
*
* Return: If new_size == old_size - ptr.
*         If new_size == 0 and ptr is not NULL - NULL.
*         Otherwise - a pointer to the reallocated memory block.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *mem;
char *ptr_cp, *filler;
unsigned int index;

if (new_size == old_size)
return (ptr);

if (ptr == NULL)
{
mem = malloc(new_size);
if (mem == NULL)
return (NULL);

return (mem);
}

if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}

ptr_cp = ptr;
mem = malloc(sizeof(*ptr_cp) * new_size);
if (mem == NULL)
{
free(ptr);
return (NULL);
}

filler = mem;

for (index = 0; index < old_size && index < new_size; index++)
filler[index] = *ptr_cp++;

free(ptr);
return (mem);
}

/**
* assign_ln_ptr - Reassigns the ln_ptr variable for _getline.
* @ln_ptr: A buffer to store an input string.
* @n: The size of ln_ptr.
* @buffer: The string to assign to ln_ptr.
* @b: The size of buffer.
*/
void assign_ln_ptr(char **ln_ptr, size_t *n, char *buffer, size_t b)
{
if (*ln_ptr == NULL)
{
if (b > 120)
*n = b;
else
*n = 120;
*ln_ptr = buffer;
}
else if (*n < b)
{
if (b > 120)
*n = b;
else
*n = 120;
*ln_ptr = buffer;
}
else
{
_strcpy(*ln_ptr, buffer);
free(buffer);
}
}

/**
* _getline - Reads input from a stream.
* @ln_ptr: A buffer to store the input.
* @n: The size of ln_ptr.
* @stream: The stream to read from.
*
* Return: The number of bytes read.
*/
ssize_t _getline(char **ln_ptr, size_t *n, FILE *stream)
{
static ssize_t input;
ssize_t ret;
char c = 'x', *buffer;
int r;

if (input == 0)
fflush(stream);
else
return (-1);
input = 0;

buffer = malloc(sizeof(char) * 120);
if (!buffer)
return (-1);

while (c != '\n')
{
r = read(STDIN_FILENO, &c, 1);
if (r == -1 || (r == 0 && input == 0))
{
free(buffer);
return (-1);
}
if (r == 0 && input != 0)
{
input++;
break;
}

if (input >= 120)
buffer = _realloc(buffer, input, input + 1);

buffer[input] = c;
input++;
}
buffer[input] = '\0';

assign_ln_ptr(ln_ptr, n, buffer, input);

ret = input;
if (r != 0)
input = 0;
return (ret);
}
