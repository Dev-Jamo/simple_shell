#include "shell_master.h"

/**
 * _eputs - Print an input string to stderr.
 * @str: String to be printed.
 **/
void _eputs(char *str)
{
	if (str)
		write(2, str, _strlen(str));
}

/**
 * _putfd - Write the character c to the given fd.
 * @c: Character to print.
 * @fd: File descriptor to write to.
 * Return: On success 1, on error -1, and errno set appropriately.
 **/
int _putfd(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
 * _putsfd - Print an input string to the given fd.
 * @str: String to be printed.
 * @fd: File descriptor to write to.
 * Return: Number of chars put.
 **/
int _putsfd(char *str, int fd)
{
	if (str)
		return (write(fd, str, _strlen(str)));
	return (0);
}


