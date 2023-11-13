#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * is_cmd - checks if a file is an executable cmd
 * @path: path to the file
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(const char *path)
{
	struct stat st;

	if (!path || stat(path, &st) != 0)
	{
		(return 0);
	}

	(return S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}

/**
 * find_path - finds the cmd in the PATH str
 * @pathstr: PATH str
 * @cmd: cmd to find
 * Return: full path of cmd if found or NULL.
 */
char *find_path(const char *pathstr, const char *cmd)
{
	if (!pathstr || !cmd)
	{
		(return NULL);
	}

	if (strncmp(cmd, "./", 2) == 0 && is_cmd(cmd))
	{
		(return strdup(cmd));
	}

	const char *start = pathstr;
	const char *end = strchr(start, ':');
	char *path = NULL;

	while (end != NULL || *start != '\0')
	{
		if (end == NULL)
		{
			end = start + strlen(start);
		}

		int len = end - start;

		path = malloc(len + strlen(cmd) + 2);

		if (path == NULL)
		{
			perror("malloc");
			(return NULL);
		}

		strncpy(path, start, len);
		path[len] = '/';
		strcpy(path + len + 1, cmd);

		if (is_cmd(path))
		{
			(return path);
		}

		free(path);

		if (*end == ':')
		{
			start = end + 1;
			end = strchr(start, ':');
		}
		else
		{
			break;
		}
	}

	(return NULL);
}
