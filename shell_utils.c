#include "shell_master.h"
#include <ctype.h>

/**
 * is_interactive_mode - return true
 * if the shell is correctly in interactive mode
 * @shell_info: structure address
 * Return: 1 for interactive mode, 0 otherwise
 **/
int is_interactive_mode(info_t *shell_info)
{
return (isatty(STDIN_FILENO) && shell_info->read_fd <= 2);
}

/**
 * is_delimiter - check if char is a delimiter
 * @c: the char to check
 * @delimiters: delimiter string
 * Return: 1 if true, 0 if false
 **/
int is_delimiter(char c, char *delimiters)
{
while (*delimiters)
if (*delimiters++ == c)
return (1);
return (0);
}

/**
 * is_alpha_character - check for alpha char
 * @c: The char to input
 * Return: 1 if c is char, 0 otherwise
 **/
int is_alpha_character(int c)
{
return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0);
}

/**
 * string_to_integer - Convert a string to an int
 * @s: String to be converted
 * Return: 0 if no numb in strings... converted numb otherwise
 **/
int string_to_integer(char *s)
{
int i, sign = 1, result = 0;

for (i = 0; s[i] != '\0'; i++)
{
if (s[i] == '-')
{
sign *= -1;
}
else if (isdigit(s[i]))
{
result *= 10;
result += (s[i] - '0');
}
else if (result > 0)
{
break; /* Stop on encountering non-digit after digits */
}
}

int output = (sign == -1) ? -result : result;
return (output);
}


