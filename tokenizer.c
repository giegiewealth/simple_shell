#include "shell.h"

/**
<<<<<<< HEAD
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
=======
* **strtow - splits a string into words. Repeat delimiters are ignored.....
* @str: the input string.....
* @d: the delimeter string.....
* Return: a pointer to an array of strings, or NULL on failure.....
*/

char **strtow(char *str, char *d)
{
int index, j_index, k_index, m_index, number_words = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (index = 0; str[index] != '\0'; index++)
if (!is_delim(str[index], d) && (is_delim(str[index + 1], d)
|| !str[index + 1]))
number_words++;
if (number_words == 0)
return (NULL);
s = malloc((1 + number_words) *sizeof(char *));
if (!s)
return (NULL);
for (index = 0, j_index = 0; j_index < number_words; j_index++)
{
while (is_delim(str[index], d))
index++;
k_index = 0;
while (!is_delim(str[index + k_index], d) && str[index + k_index])
k_index++;
s[j_index] = malloc((k_index + 1) * sizeof(char));
if (!s[j_index])
{
for (k_index = 0; k_index < j_index; k_index++)
free(s[k_index]);
free(s);
return (NULL);
}
for (m_index = 0; m_index < k_index; m_index++)
s[j_index][m_index] = str[index++];
s[j_index][m_index] = 0;
}
s[j_index] = NULL;
return (s);
}

/**
* **strtow2 - splits a string into words.......
* @str: the input string.......
* @d: the delimeter.......
* Return: a pointer to an array of strings, or NULL on failure......
*/
char **strtow2(char *str, char d)
{
int i_index, j_index, k_index, m, number_words = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
for (i_index = 0; str[i_index] != '\0'; i_index++)
if ((str[i_index] != d && str[i_index + 1] == d) ||
(str[i_index] != d && !str[i_index + 1]) || str[i_index + 1] == d)
number_words++;
if (number_words == 0)
return (NULL);
s = malloc((1 + number_words) *sizeof(char *));
if (!s)
return (NULL);
for (i_index = 0, j_index = 0; j_index < number_words; j_index++)
{
while (str[i_index] == d && str[i_index] != d)
i_index++;
k_index = 0;
while (str[i_index + k_index] != d &&
str[i_index + k_index] && str[i_index + k_index] != d)
k_index++;
s[j_index] = malloc((k_index + 1) * sizeof(char));
if (!s[j_index])
{
for (k_index = 0; k_index < j_index; k_index++)
free(s[k_index]);
free(s);
return (NULL);
}
for (m = 0; m < k_index; m++)
s[j_index][m] = str[i_index++];
s[j_index][m] = 0;
}
s[j_index] = NULL;
return (s);
>>>>>>> 0bf15ae349fab10062ba030b1e6a25fc398050af
}
