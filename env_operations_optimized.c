#include "shell_master.h"

/**
 * update_environment - updates the string array copy of our environment
 * @info: structure with potential arguments.
 * Return: Always 0
 */
char **update_environment(info_t *info)
{
	if (!info->environment || info->env_changed)
	{
		free_string_array(info->environment);
		info->environment = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environment);
}

/**
 * remove_environment_variable - removes an environment variable
 * @info: structure with potential arguments.
 * @variable: environment variable property
 * Return: 1 on delete, 0 otherwise.
 */
int remove_environment_variable(info_t *info, char *variable)
{
	if (!info->env || !variable)
		return (0);

	size_t index = 0;
	list_t *node = info->env;
	char *prefix;

	while (node)
	{
		prefix = starts_with(node->str, variable);
		if (prefix && *prefix == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}

	return (info->env_changed);
}

/**
 * set_environment_variable - initializes a new environment variable
 * or modifies an existing one
 * @info: structure with potential arguments.
 * @variable: environment variable property
 * @value: environment variable value
 * Return: Always 0.
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	if (!variable || !value)
		return (0);

	char *env_entry = concat_strings(variable, "=", value);

	if (!env_entry)
		return (1);

	list_t *node = info->env;
	char *prefix;

	while (node)
	{
		prefix = starts_with(node->str, variable);
		if (prefix && *prefix == '=')
		{
			free(node->str);
			node->str = env_entry;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), env_entry, 0);
	free(env_entry);
	info->env_changed = 1;
	return (0);
}

