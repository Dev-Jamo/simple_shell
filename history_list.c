#include "history.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * build_history_list - Builds a history list with the provided information.
 * @info: Pointer to the info_t structure.
 * @buffer: Pointer to the character buffer.
 * @line_count: Number of lines in the buffer.
 *
 * Return: Always returns 0.
 */
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
 * renumber_history - Renumber the history list nodes.
 * @info: Pointer to the info_t structure.
 *
 * Return: Returns the updated histcount.
 */
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


