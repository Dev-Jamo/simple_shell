#include "shell_master.h"

/**
 * update_environment - updates the string array copy of our environment
 * @info: structure with potential arguments.
 * Return: Always 0
 */
void free_string_array(char **array);

char **update_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = list_to_strings(info->environ);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * remove_environment_variable - removes an environment variable
 * @info: structure with potential arguments.
 * @variable: environment variable property
 * Return: 1 on delete, 0 otherwise.
 */
int set_environ_variable(info_t *info, char *variable, char *value)
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

/**
 * set_environment_variable - initializes a new environment variable
 * or modifies an existing one
 * @info: structure with potential arguments.
 * @variable: environment variable property
 * @value: environment variable value
 * Return: Always 0.
 */
int set_environ_variable(info_t *info, char *variable, char *value)
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

