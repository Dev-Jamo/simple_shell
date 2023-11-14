#include "shell_master.h"

/**
 * display_history - display history list by one command line
 * @info: Struct contain potential arg to maintain
 *
 * Description: Proceed with line number starting at 0
 * Return: Always 0
 **/
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - remove alias from string
 * @info: parameter structure
 * @alias_str: string alias
 *
 * Return: 0 on success or 1 on error
 **/
int unset_alias(info_t *info, char *alias_str)
{
	char *equal_sign_pos = strchr(alias_str, '=');

	if (!equal_sign_pos)
	{
		return (1);
	}

	char alias_separator = *equal_sign_pos;
	*equal_sign_pos = '\0';

	int result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*equal_sign_pos = alias_separator;

	return (result);
}

/**
 * set_alias - set alias to string
 * @info: parameter structure
 * @alias_str: string alias
 *
 * Return: 0 on success or 1 on error
 **/
int set_alias(info_t *info, char *alias_str)
{
	char *equal_sign_pos = strchr(alias_str, '=');

	if (!equal_sign_pos)
	{
		return (1);
	}

	if (!*++equal_sign_pos)
	{
		return (unset_alias(info, alias_str));
	}

	unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - print alias string
 * @alias_node: Alias node
 *
 * Return: 0 on success or 1 on error
 **/
int print_alias(list_t *alias_node)
{
	if (alias_node)
	{
		char *equal_sign_pos = strchr(alias_node->str, '=');

		if (equal_sign_pos)
		{
			for (char *alias_char = alias_node->str;
					alias_char <= equal_sign_pos; alias_char++)
			{
				_putchar(*alias_char);
			}
			_putchar('\'');
			_puts(equal_sign_pos + 1);
			_puts("'\n");
			return (0);
		}
	}
	return (1);
}

/**
 * alias_command - mimics alias builtin
 * @info: Structure contain potential arguments to maintain
 *
 * Return: 0
 **/
int alias_command(info_t *info)
{
	if (info->argc == 1)
	{
		list_t *alias_node = info->alias;

		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (int i = 1; info->argv[i]; i++)
	{
		char *equal_sign_pos = strchr(info->argv[i], '=');

		if (equal_sign_pos)
		{
			set_alias(info, info->argv[i]);
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}


