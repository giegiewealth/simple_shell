#include "shell.h"

/**
<<<<<<< HEAD
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
=======
* bfree - frees a pointer and NULLs the address......
* @ptr: address of the pointer to free.....
*
* Return: 1 if freed, otherwise 0......
*/
int bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af
}
