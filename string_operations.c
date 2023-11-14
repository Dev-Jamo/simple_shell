#include "shell_master.h"

/**
 * custom_strncpy - copies a string
 * @destination: destination string to be copied to
 * @source: source string
 * @num_chars: number of characters to be copied
 * Return: the concatenated string
 **/
char *custom_strncpy(char *destination, const char *source, size_t num_chars)
{
	size_t i;

	for (i = 0; i < num_chars - 1 && source[i] != '\0'; i++)
		destination[i] = source[i];

	for (; i < num_chars; i++)
		destination[i] = '\0';

	return (destination);
}

/**
 * custom_strncat - concatenates two strings
 * @destination: first string
 * @source: second string
 * @max_chars: number of bytes to be maximally used
 * Return: the concatenated string
 **/
char *custom_strncat(char *destination, const char *source, size_t max_chars)
{
	size_t i, j;

	for (i = 0; destination[i] != '\0'; i++)
		;

	for (j = 0; j < max_chars && source[j] != '\0'; i++, j++)
		destination[i] = source[j];

	destination[i] = '\0';

	return (destination);
}

/**
 * custom_strchr - locates a character in a string
 * @str: string to be parsed
 * @character: character to look for
 * Return: a pointer to the memory area str
 **/
char *custom_strchr(const char *str, int character)
{
	do {
		if (*str == character)
			return ((char *)str);
	} while (*str++ != '\0');

	return (NULL);
}


