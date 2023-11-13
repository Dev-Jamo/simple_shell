#include "shell_master.h"

/**
 * list_len - Calculate the length of a linked list.
 * @head: Pointer to the first node of the linked list.
 *
 * Return: The number of nodes in the list.
 */
size_t list_len(const list_t *head)
{
	size_t count = 0;
	const list_t *current = head;

	while (current)
	{
		count++;
		current = current->next;
	}

	return count;
}

/**
 * list_to_strings - Convert a linked list of strings to an array of strings.
 * @head: Pointer to the first node of the linked list.
 *
 * Return: An array of strings or NULL on failure.
 */
char **list_to_strings(const list_t *head)
{
	size_t count = list_len(head);
	char **strs;
	size_t i = 0;

	if (!head || count == 0)
		return NULL;

	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return NULL;

	for (; head; head = head->next)
	{
		strs[i] = strdup(head->str);
		if (!strs[i])
		{
			while (i > 0)
				free(strs[--i]);
			free(strs);
			return NULL;
		}
		i++;
	}

	strs[count] = NULL;
	return strs;
}

/**
 * print_list - Print the elements of a linked list.
 * @h: Pointer to the first node of the linked list.
 *
 * Return: The number of nodes printed.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		const char *str = h->str;
		if (!str || *str == '\0')
			str = "(nil)";

		if (_puts(convert_number(h->num, 10, 0)) == -1 || _putchar(':') == -1 ||
			_putchar(' ') == -1 || _puts(str) == -1 || _putchar('\n') == -1)
		{
			return i;
		}

		h = h->next;
		i++;
	}

	return i;
}

/**
 * node_starts_with - Find a node whose string starts with a prefix and optionally matches a character.
 * @head: Pointer to the first node of the linked list.
 * @prefix: The prefix to match.
 * @c: The character to match (-1 for any character).
 *
 * Return: A matching node or NULL if no match is found.
 */
list_t *node_starts_with(const list_t *head, const char *prefix, char c)
{
	const list_t *current_node = head;

	while (current_node)
	{
		const char *str = current_node->str;

		if (starts_with(str, prefix))
		{
			if (c != -1 && str[strlen(prefix)] != c)
			{
				current_node = current_node->next;
				continue;
			}

			return (list_t *)current_node;
		}

		current_node = current_node->next;
	}

	return NULL;
}

/**
 * get_node_index - Get the index of a node in a linked list.
 * @head: Pointer to the first node of the linked list.
 * @node: Pointer to the node to find.
 *
 * Return: The index of the node if found, or (size_t)-1 if not found.
 */
size_t get_node_index(const list_t *head, const list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;

		head = head->next;
		index++;
	}

	return (size_t)-1;
}
