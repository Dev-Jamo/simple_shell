#include "shell_master.h"

/**
 *	clear_info - Initializes the fields of the info_t structure to NULL or 0.
 *	@info: Pointer to the info_t structure to be cleared.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 *	set_info - Sets the fields of the info_t structure
 *	based on the provided arguments.
 *	@info: Pointer to the info_t structure to be set.
 *	@args: Array of strings representing command arguments.
 */
void set_info(info_t *info, char **args)
{
	info->fname = args[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = (char **)malloc(sizeof(char *) * 2);

			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		info->argc = info->argv ? array_size(info->argv) : 0;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 *	free_info - Frees the memory occupied by the fields of the info_t structure.
 *	@info: Pointer to the info_t structure to be freed.
 *	@freeAll: Flag indicating whether to free all resources.
 */
void free_info(info_t *info, int freeAll)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (freeAll)
	{
		free(info->arg);
		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);

		if (info->readfd > 2)
		{
			close(info->readfd);
		}

		_putchar(BUF_FLUSH);
	}
}


