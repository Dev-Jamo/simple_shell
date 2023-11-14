#ifndef HISTORY_H
#define HISTORY_H

#include <stddef.h>

/**
 * struct info - Structure to hold information.
 *
 * Description: Define your info struct members here.
 */
typedef struct info
{
	/* Define your info struct members here */
} info_t;

/**
 * struct list - Structure to represent a linked list node.
 *
 * @str: String data.
 * @num: Integer data.
 * @next: Pointer to the next node in the list.
 */
typedef struct list
{
	char *str;
	int num;
	struct list *next;
} list_t;

/**
 * get_history_file - Get the history file for the given info.
 *
 * @info: Pointer to the info structure.
 * Return: A string representing the history file.
 */
char *get_history_file(info_t *info);

/**
 * write_history_file - Write history to the specified file descriptor.
 *
 * @fd: File descriptor to write to.
 * @history: Pointer to the history list.
 */
void write_history_file(ssize_t fd, list_t *history);

/**
 * write_history - Write history to the file for the given info.
 *
 * @info: Pointer to the info structure.
 * Return: 0 on success, -1 on failure.
 */
int write_history(info_t *info);

/**
 * read_history_file - Read history from the specified file descriptor.
 *
 * @info: Pointer to the info structure.
 * @hist_fd: File descriptor to read from.
 * @hist_stat: Pointer to the struct stat to store file information.
 * Return: 0 on success, -1 on failure.
 */
int read_history_file(info_t *info, int hist_fd, struct stat *hist_stat);

/**
 * read_history - Read history from the file for the given info.
 *
 * @info: Pointer to the info structure.
 * Return: 0 on success, -1 on failure.
 */
int read_history(info_t *info);

/**
 * build_history_list - Build a linked list from the history buffer.
 *
 * @info: Pointer to the info structure.
 * @buffer: Buffer containing history data.
 * @line_count: Number of lines in the buffer.
 * Return: 0 on success, -1 on failure.
 */
int build_history_list(info_t *info, char *buffer, int line_count);

/**
 * renumber_history - Renumber the history list.
 *
 * @info: Pointer to the info structure.
 * Return: 0 on success, -1 on failure.
 */
int renumber_history(info_t *info);

#endif /* HISTORY_H */


