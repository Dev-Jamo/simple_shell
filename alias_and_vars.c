#include "shell_master.h"

/**
 * is_chain - test if current char in buffer is a chain delimiter.
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	char currentChar = buf[j];
	char nextChar = buf[j + 1];

	if ((currentChar == '|' || currentChar == '&') && currentChar == nextChar)
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = (currentChar == '|') ? CMD_OR : CMD_AND;
	}
	else if (currentChar == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}

	*p = j;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last status.
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf.
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if ((info->cmd_buf_type == CMD_AND && info->status) ||
			(info->cmd_buf_type == CMD_OR && !info->status))
	{
	buf[i] = 0;
	j = len;
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string.
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise.
 */
#include <string.h>

int replace_alias(info_t *info)
{
	list_t *node;
	char *p;

	char *newArgv0;

	node = node_starts_with(info->alias, info->argv[0], '=');
	if (!node)
		return (0);

	p = _strchr(node->str, '=');
	if (!p)
		return (0);

	p++;

	newArgv0 = _strdup(p);

	if (!newArgv0)
		return (0);

	free(info->argv[0]);
	info->argv[0] = newArgv0;

	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string.
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
	char *arg = info->argv[i];

	if (arg[0] != '$' || arg[1] == '\0')
	continue;

	if (strcmp(arg, "$?") == 0)
	{
		char status_str[12];

		snprintf(status_str, sizeof(status_str), "%d", info->status);
		replace_string(&info->argv[i], _strdup(status_str));
	}
	else if (strcmp(arg, "$$") == 0)
	{
		char pid_str[12];

		snprintf(pid_str, sizeof(pid_str), "%d", getpid());
		replace_string(&info->argv[i], _strdup(pid_str));
	}
	else
	{
		node = node_starts_with(info->env, &arg[1], '=');
		if (node)
		{
			char *value = _strchr(node->str, '=') + 1;

			replace_string(&info->argv[i], _strdup(value));
		}
	else
		{
			replace_string(&info->argv[i], _strdup(""));
		}
	}
	}
	return (0);
}

/**
 * replace_string - replaces string.
 * @old: address of old string.
 * @new: new string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	if (*old != new)
	{
	free(*old);
	*old = new;
	}
	return (1);
}
