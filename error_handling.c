#include "shell_master.h"

/**
 * _erratoi - Converts a string to an unsigned long long integer.
 * @str: The input string to be converted.
 *
 * Description: Handles leading '+' sign. Checks for valid digits and
 * avoids overflow.
 *
 * Return: The converted integer or -1 if there is an error.
 */
int _erratoi(char *str)
{
	unsigned long long int result = 0;

	if (*str == '+')
		str++;

	for (; *str != '\0'; str++)
	{
		if (*str >= '0' && *str <= '9')
		{
			result *= 10;
			result += (*str - '0');
			if (result > LLONG_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * print_error - Prints an error message to standard error.
 * @info: Information structure containing filename, line count,
 *        executable name, etc.
 * @error_type: Type of error to be printed.
 *
 * Description: Uses information from the `info` structure to
 * construct the error message.
 */
void print_error(info_t *info, char *error_type)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_d - Prints an integer to a specified file descriptor.
 * @input: The integer to be printed.
 * @fd: File descriptor where the output should be printed.
 *
 * Description: Handles negative numbers and uses either `_eputchar` or
 * `_putchar`
 * depending on the file descriptor. Uses a divisor loop to extract and
 * print each digit.
 *
 * Return: The count of characters printed.
 */
int print_d(int input, int fd)
{
	int (*write_char)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;
	unsigned int absolute_value = (input < 0) ? -input : input;
	unsigned int current = absolute_value;

	if (input < 0)
	{
		write_char('-');
		count++;
	}

	for (size_t divisor = 1000000000; divisor > 1; divisor /= 10)
	{
		if (absolute_value / divisor)
		{
			write_char('0' + current / divisor);
			count++;
		}
		current %= divisor;
	}

	write_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a long integer to a string
 * representation in a specified base.
 * @num: The long integer to be converted.
 * @base: The base for the conversion.
 * @flags: Flags indicating conversion options.
 *
 * Description: Supports conversion to hexadecimal, decimal, or other bases.
 * Handles signed and unsigned numbers.
 *
 * Return: A pointer to the allocated string.
 */
char *convert_number(long int num, int base, int flags)
{
	char *character_set = (flags & CONVERT_LOWERCASE) ?
		"0123456789abcdef" : "0123456789ABCDEF";
	char *result;
	char sign = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? '-' : '\0';
	unsigned long absolute_value = (num < 0) ? -num : num;

	size_t length = snprintf(NULL, 0, "%c", sign) + 1;
	/* Length for the sign and null terminator */

	do {
		length++;
		absolute_value /= base;
	} while (absolute_value != 0);

	result = (char *)malloc(length);
	if (!result)
		return (NULL);

	char *ptr = result + length - 1;
	*ptr = '\0';

	do {
		*--ptr = character_set[absolute_value % base];
		absolute_value /= base;
	} while (absolute_value != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - Removes comments from a string
 * (assumed to be a line of code).
 * @line: The input string containing a line of code.
 *
 * Description: Considers a '#' character as
 * the beginning of a comment if it is at
 * the start of the line or preceded by a space.
 * Modifies the input string by replacing
 * the comment part with a null terminator.
 */
void remove_comments(char *line)
{
	size_t index;

	for (index = 0; line[index] != '\0'; index++)
	{
		if (line[index] == '#' && (index == 0 || line[index - 1] == ' '))
		{
			line[index] = '\0';
			break;
		}
	}
}


