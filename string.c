#include "shell.h"

/**
* _strlen - returns the length of a string......
* @s: the string whose length to check......
*
* Return: integer length of string......
*/
int _strlen(char *s)
{
int index = 0;

if (!s)
return (0);

while (*s++)
index++;
return (index);
}

/**
* _strcmp - performs lexicogarphic comparison of two strangs.......
* @string1: the first strang......
* @string2: the second strang......
*
* Return: negative if string1 < string2,
* positive if string1 > string2,
* zero if string1 == string2......
*/
int _strcmp(char *string1, char *string2)
{
while (*string1 && *string2)
{
if (*string1 != *string2)
return (*string1 - *string2);
string1++;
string2++;
}
if (*string1 == *string2)
return (0);
else
return (*string1 < *string2 ? -1 : 1);
}

/**
* starts_with - checks if needle starts
* with haystack......
* @haystack: string to search......
* @needle: the substring to find......
*
* Return: address of next char of
* haystack or NULL......
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
* _strcat - concatenates two strings.....
* @dest: the destination buffer.....
* @src: the source buffer.....
*
* Return: pointer to destination buffer.....
*/
char *_strcat(char *dest, char *src)
{
char *ret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
