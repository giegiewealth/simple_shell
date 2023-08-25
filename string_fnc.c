#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dst, const char *source);
char *_strcat(char *dst, const char *source);
char *_strncat(char *dst, const char *source, size_t n);

/**
* _strlen - Returns the length of a string.
* @s: A pointer to the characters string.
*
* Return: The length of the character string.
*/
int _strlen(const char *s)
{
int length = 0;

if (!s)
return (length);
for (length = 0; s[length]; length++)
;
return (length);
}

/**
* _strcpy - Copies the string pointed to by source, including the
*           terminating null byte, to the buffer pointed by des.
* @dst: Pointer to the destination of copied string.
* @source: Pointer to the source of the source string.
*
* Return: Pointer to dst.
*/
char *_strcpy(char *dst, const char *source)
{
size_t i;

for (i = 0; source[i] != '\0'; i++)
dst[i] = source[i];
dst[i] = '\0';
return (dst);
}

/**
* _strcat - Concantenates two strings.
* @dst: Pointer to destination string.
* @source: Pointer to source string.
*
* Return: Pointer to destination string.
*/
char *_strcat(char *dst, const char *source)
{
char *dest_tmp;
const char *source_tmp;

dest_tmp = dst;
source_tmp = source;

while (*dest_tmp != '\0')
dest_tmp++;

while (*source_tmp != '\0')
*dest_tmp++ = *source_tmp++;
*dest_tmp = '\0';
return (dst);
}

/**
* _strncat - Concactenates two strings where n number
*            of bytes are copied from source.
* @dst: Pointer to destination string.
* @source: Pointer to source string.
* @n: n bytes to copy from source.
*
* Return: Pointer to destination string.
*/
char *_strncat(char *dst, const char *source, size_t n)
{
size_t len_dest = _strlen(dst);
size_t i;

for (i = 0; i < n && source[i] != '\0'; i++)
dst[len_dest + i] = source[i];
dst[len_dest + i] = '\0';

return (dst);
}
