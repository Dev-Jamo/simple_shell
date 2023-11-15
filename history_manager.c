#include "shell_master.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: Allocated string containing history file.
 **/
char *get_history_file(info_t *info)
{
	char *home_directory = _getenv(info, "HOME=");

	if (!home_directory)
		return (NULL);

	size_t len = _strlen(home_directory) + _strlen(HIST_FILE) + 2;
	char *history_file_path = malloc(len);

	if (!history_file_path)
	{
		free(home_directory);
		return (NULL);
	}

	_strcpy(history_file_path, home_directory);
	_strcat(history_file_path, "/");
	_strcat(history_file_path, HIST_FILE);
	free(home_directory);

	return (history_file_path);
}

/**
 * write_history_file - writes history to a file descriptor
 * @fd: file descriptor
 * @history: history linked list
 *
 * Return: void
 **/
void write_history_file(ssize_t fd, list_t *history)
{
	for (list_t *current_node = history; current_node;
			current_node = current_node->next)
	{
		_putsfd(current_node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
}

/**
 * write_history - creates a file or appends to an existing file
 * @info: parameter struct
 *
 * Return: 1 on success, else -1.
 **/
int write_history(info_t *info)
{
	char *history_filename = get_history_file(info);

	if (!history_filename)
		return (-1);

	ssize_t history_fd = open(history_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(history_filename);

	if (history_fd == -1)
		return (-1);

	write_history_file(history_fd, info->history);

	close(history_fd);
	return (1);
}

/**
 * read_history_file - reads history from a file descriptor
 * @info: parameter struct
 * @hist_fd: history file descriptor
 * @hist_stat: pointer to history file stat structure
 *
 * Return: Histcount on success, 0 otherwise.
 **/
int read_history_file(info_t *info, int hist_fd, struct stat *hist_stat)
{
	char *hist_content = malloc(hist_stat->st_size + 1);

	if (!hist_content)
	{
		close(hist_fd);
		return (0);
	}

	ssize_t read_length = read(hist_fd, hist_content, hist_stat->st_size);

	close(hist_fd);

	if (read_length <= 0)
	{
		free(hist_content);
		return (0);
	}

	hist_content[hist_stat->st_size] = '\0';
	int line_count = 0;
	int last_index = 0;

	for (int i = 0; i < hist_stat->st_size; i++)
	{
		if (hist_content[i] == '\n')
		{
			hist_content[i] = '\0';
			build_history_list(info, hist_content + last_index, line_count++);
			last_index = i + 1;
		}
	}

	if (last_index != hist_stat->st_size)
		build_history_list(info, hist_content + last_index, line_count++);
	free(hist_content);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * read_history - reads history from a file
 * @info: parameter struct
 *
 * Return: Histcount on success, 0 otherwise.
 **/
int read_history(info_t *info)
{
	char *history_filename = get_history_file(info);

	if (!history_filename)
		return (0);

	ssize_t history_fd = open(history_filename, O_RDONLY);

	free(history_filename);

	if (history_fd == -1)
		return (0);

	struct stat history_stat;

	if (fstat(history_fd, &history_stat) != 0 || history_stat.st_size < 2)
	{
		close(history_fd);
		return (0);
	}

	return (read_history_file(info, history_fd, &history_stat));
}

/**
 * build_history_list - adds an entry to a history linked list
 * @info: structure containing potential arg.
 * @buffer: buffer
 * @line_count: history line count, histcount
 *
 * Return: Always 0.
 **/
int build_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *current_node = NULL;

	if (info->history)
		current_node = info->history;

	add_node_end(&current_node, buffer, line_count);

	if (!info->history)
		info->history = current_node;

	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: structure containing potential arg
 *
 * Return: New histcount.
 **/
int renumber_history(info_t *info)
{
	list_t *current_node = info->history;
	int i = 0;

	while (current_node)
	{
		current_node->num = i++;
		current_node = current_node->next;
	}

	return (info->histcount = i);
}

