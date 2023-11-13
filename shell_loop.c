#include "shell_master.h"

/**
 * hsh - Main shell loop
 * @info: param & return info struct
 * @av: arg vector from main()
 * Return: 0 on success, 1 on error, or error code.
 **/
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);

		if (interactive(info))
		{
			_puts("$ ");
		}

		_eputchar(BUF_FLUSH);
		r = get_input(info);

		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);

			if (builtin_ret == -1)
			{
				find_cmd(info);
			}
		}
		else if (interactive(info))
		{
			_putchar('\n');
		}

		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
	{
		exit(info->status);
	}

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
		{
			exit(info->status);
		}

		exit(info->err_num);
	}

	(return builtin_ret);
}

/**
 * find_builtin - it finds a builtin command.
 * @info: param & return info struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit().
 **/
int find_builtin(info_t *info)
{
	int built_in_ret = -1;

	const builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (int i = 0; builtintbl[i].type != NULL; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}

	(return built_in_ret);
}

/**
 * find_cmd - Finds a cmd in PATH
 * @info: param & return info struct.
 **/
void find_cmd(info_t *info)
{
	char *path = NULL;
	int numArgs = 0;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (int argIndex = 0; info->arg[argIndex]; argIndex++)
	{
		if (!is_delim(info->arg[argIndex], " \t\n"))
		{
			numArgs++;
		}
	}

	if (numArgs == 0)
	{
		return;
	}

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/')
				&& is_cmd(info, info->argv[0]))
		{
			fork_cmd(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Command not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an exec thread to run cmd
 * @info: param & return info struct.
 **/
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			perror("Execve error:");
			free_info(info, 1);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == PERMISSION_DENIED_ERROR)
			{
				print_error(info, "Permission denied\n");
			}
		}
	}
}
