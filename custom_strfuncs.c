#include "shell_master.h"
#include <unistd.h>

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments to maintain
 *           const func prototype.
 * Return: exit with exit status (0) else info.argv[0] != "exit"
 **/
int exit_shell(info_t *info)
{
	if (info->argv[1])
	{
		int exit_check = _erratoi(info->argv[1]);

		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_check;
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - change current directory of the process
 * @info: Structure containing potential arguments to maintain
 * const func proto.
 * Return: 0
 **/
int change_directory(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
	{
		printf("TODO: >>getcwd failure emsg here<<\n");
	}
	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_ret = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			printf("%s\n", current_dir);
			return (0);
		}
		printf("%s\n", _getenv(info, "OLDPWD="));
		chdir_ret = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));	}
	return (0);
}

/**
 * help_command - change current directory of the process.
 * @info: Structure containing potential arguments to maintain
 * const funct protot.
 * Return:  0
 **/
int help_command(info_t *info)
{
	char **arg_array = info->argv;

	printf("help call works. Function not yet implemented\n");

	if (0)
	{
		printf("%s\n", *arg_array);
	}

	return (0);
}


