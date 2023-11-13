#include "shell_master.h"

/**
 * is_delim - Check if a character is a delimiter.
 * @c: Character to check.
 * @delimiters: String containing delimiter characters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, const char *delimiters)
{
	if (!delimiters)
	delimiters = " ";

	(return strchr(delimiters, c) != NULL);
}

/**
 * count_words - Count the number of words in a string.
 * @str: String to count words in.
 * @delimiters: String containing delimiter characters.
 * Return: The number of words.
 */
static int count_words(const char *str, const char *delimiters)
{
}

/**
 * allocate_and_copy - Allocate memory and copy a substring.
 * @str: Source string.
 * @start: Starting index.
 * @end: Ending index.
 * Return: Pointer to the duplicated substring.
 */
static char *allocate_and_copy(const char *str, int start, int end)
{
}

/**
 * strtow - Split a string into words.
 * @str: String to be split.
 * @delimiters: String containing delimiter characters.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, const char *delimiters)
{
	if (str == NULL || str[0] == '\0')
	(return NULL);

	int i = 0, j = 0, numwords = count_words(str, delimiters);
	char **s;

	if (numwords == 0)
	(return NULL);

	s = (char **)malloc((numwords + 1) * sizeof(char *));
	if (!s)
	(return NULL);

	(return s);
}
