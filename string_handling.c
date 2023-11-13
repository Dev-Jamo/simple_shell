#include <stdlib.h>
#include <unistd.h>

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'

/**
 * copy_string - Copy a string.
 * @destination: Destination string
 * @source: Source string.
 * Return: Pointer to destination.
 */
char *copy_string(char *destination, const char *source)
{
	int i = 0;

	if (destination == source || source == NULL)
		(return destination);

	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}

	destination[i] = '\0';
	(return destination);
}

/**
 * duplicate_string - Duplicate a string.
 * @string_to_duplicate: String to duplicate.
 * Return: Pointer to the duplicated string or NULL on failure.
 */
char *duplicate_string(const char *string_to_duplicate)
{
	if (string_to_duplicate == NULL)
		(return NULL);

	size_t length = 0;

	while (string_to_duplicate[length])
		length++;

	char *result = malloc(sizeof(char) * (length + 1));

	if (!result)
		(return NULL);

	for (size_t i = 0; i < length; i++)
		result[i] = string_to_duplicate[i];

	result[length] = '\0';
	(return result);
}

/**
 * print_string - Print a string to the stdout.
 * @string_to_print: String to be printed.
 */
void print_string(const char *string_to_print)
{
	if (!string_to_print)
		return;

	int i = 0;

	while (string_to_print[i] != '\0')
	{
		write_character(string_to_print[i]);
		i++;
	}
}

/**
 * write_character - Write a character to stdout.
 * @character_to_write: Character to print
 * Return: On success 1, on error -1.
 */
int write_character(char character_to_write)
{
	static int i = 1;
	static char buffer[WRITE_BUF_SIZE];

	if (character_to_write == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}

	if (character_to_write != BUF_FLUSH)
		buffer[i++] = character_to_write;

	(return 1);
}
