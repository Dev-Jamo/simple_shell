#include "shell_master.h"
#include <stddef.h> 

/**
 * _strlen - Get the length of a string
 * @s: The string to measure
 * Return: The length of the string
 */
size_t _strlen(const char *s)
{
	if (!s)
		return 0;

	size_t length = 0;
	while (s[length] != '\0')
	{
		length++;
	}

	return length;
}

/**
 * _strcmp - Compare two strings lexicographically
 * @s1: The first string
 * @s2: The second string
 * Return:
 *   - Negative value if s1 < s2
 *   - Positive value if s1 > s2
 *   - 0 if s1 == s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/**
 * starts_with - Check if a string starts with a prefix.
 * @haystack: The string to search.
 * @needle: The prefix to find.
 * Return:
 *   - Pointer to the first character in haystack after the prefix, if found.
 *   - NULL if haystack does not start with the prefix.
 */
const char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle != *haystack)
		{
			return NULL;
		}
		needle++;
		haystack++;
	}

	return haystack;
}

/**
 * _strcat - Concatenate two strings.
 * @dest: The destination buffer.
 * @src: The source buffer to append.
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, const char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return ret;
}
