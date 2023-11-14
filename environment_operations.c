#include "shell_master.h"

/**
 * shell_print_environment - Print the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_print_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * shell_get_environment_variable - Get the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 * Return: The value or NULL.
 */
char *shell_get_environment_variable(info_t *info, const char *name)
{
	list_t *current_node = info->env;
	char *variable_value;

	while (current_node)
	{
		variable_value = starts_with(current_node->str, name);
		if (variable_value && *variable_value)
			return (variable_value);
		current_node = current_node->next;
	}

	return (NULL);
}

/**
 * shell_set_environment_variable - Initialize or modify an envi var.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * shell_unset_environment_variable - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_unset_environment_variable(info_t *info)
{
	int arg_index;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (arg_index = 1; arg_index <= info->argc; arg_index++)
		_unsetenv(info, info->argv[arg_index]);

	return (0);
}

/**
 * shell_populate_environment_list - Populate the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int shell_populate_environment_list(info_t *info)
{
	list_t *current_node = NULL;
	size_t env_index;

	for (env_index = 0; environ[env_index]; env_index++)
		add_node_end(&current_node, environ[env_index], 0);

	info->env = current_node;
	return (0);
}


