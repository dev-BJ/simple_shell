#include "main.h"
/**
* _strlen - function that calculates the length of a string
* @str: length is to be calculated
* Return: length of the string
*/
size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * _strcspn - Calculates the length of the init segment of s1 which
 * consists of only the characters not in s2.
 * @s1: The string to search in.
 * @s2: The characters to search for.
 *
 * Return: The length of the initial seg of s1
 */
size_t _strcspn(const char *s1, const char *s2)
{
	size_t len = 0, i = 0;

	while (s1[len] != '\0')
	{
		while (s2[i] != '\0')
		{
			if (s1[len] == s2[i])
			{
				return (len);
			}
			i++;
		}
		len++;
	}
	return (len);
}
