#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * get_history_file - Generates the path to the history file.
 * @info: Pointer to the info_t structure.
 * Return: A dynamically allocated string with the file path,
 * or NULL if an error occurs.
 */
char *get_history_file(info_t *info)
{
	char *home_directory = _getenv(info, "HOME=");

	if (!home_directory)
	{
		return (NULL);
	}

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
 * write_history_file - Writes history to the specified file descriptor.
 * @fd: File descriptor.
 * @history: Pointer to the list of history entries.
 */
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
 * write_history - Writes history to the file.
 * @info: Pointer to the info_t structure.
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	char *history_filename = get_history_file(info);

	if (!history_filename)
	{
		return (-1);
	}

	ssize_t history_fd = open(history_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(history_filename);

	if (history_fd == -1)
	{
		return (-1);
	}

	write_history_file(history_fd, info->history);

	close(history_fd);
	return (1);
}

/**
 * read_history_file - Reads history from the specified file descriptor.
 * @info: Pointer to the info_t structure.
 * @hist_fd: File descriptor.
 * @hist_stat: Pointer to the stat structure.
 * Return: The number of history entries read.
 */
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
	{
		build_history_list(info, hist_content + last_index, line_count++); }
	free(hist_content);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0); }
	renumber_history(info);
	return (info->histcount); }

/**
 * read_history - Reads history from the file.
 * @info: Pointer to the info_t structure.
 * Return: The number of history entries read.
 */
int read_history(info_t *info)
{
	char *history_filename = get_history_file(info);

	if (!history_filename)
	{
		return (0);
	}

	ssize_t history_fd = open(history_filename, O_RDONLY);

	free(history_filename);

	if (history_fd == -1)
	{
		return (0);
	}

	struct stat history_stat;

	if (fstat(history_fd, &history_stat) != 0 || history_stat.st_size < 2)
	{
		close(history_fd);
		return (0);
	}

	return (read_history_file(info, history_fd, &history_stat));
}


