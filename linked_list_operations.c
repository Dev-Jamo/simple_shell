#include "shell_master.h"

#define EXIT_CANNOT_OPEN_FILE   (127)
#define EXIT_FILE_ACCESS_ERROR  (126)

/**
 * add_node - Add a new node at the beginning of the list.
 * @head: A pointer to the head of the list.
 * @str: The string to be stored in the new node.
 * @node_index: The index of the new node.
 * Return: A pointer to the new node or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int node_index)
{
	list_t *new_node;

	if (!head)
	{
		return (NULL);
	}

	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}

	memset(new_node, 0, sizeof(list_t));
	new_node->num = node_index;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - Add a new node at the end of the list.
 * @head: A pointer to the head of the list.
 * @str: The string to be stored in the new node.
 * @node_index: The index of the new node.
 * Return: A pointer to the new node or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int node_index)
{
	list_t *new_node, *current_node;

	if (!head)
	{
		return (NULL);
	}

	current_node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}

	memset(new_node, 0, sizeof(list_t));
	new_node->num = node_index;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - Print the strings in the list.
 * @head: A pointer to the head of the list.
 * Return: The number of nodes in the list.
 */
size_t print_list_str(const list_t *head)
{
	size_t node_count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		node_count++;
	}

	return (node_count);
}

/**
 * delete_node_at_index - Delete a node at a specific index in the list.
 * @head: A pointer to the head of the list.
 * @target_index: The index of the node to be deleted.
 * Return: 1 if successful, 0 otherwise.
 */
int delete_node_at_index(list_t **head, size_t target_index)
{
	list_t *current_node, *prev_node;
	size_t current_index = 0;

	if (!head || !*head)
	{
		return (0);
	}

	if (!target_index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}

	current_node = *head;
	while (current_node)
	{
		if (current_index == target_index)
		{
			prev_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}

		current_index++;
		prev_node = current_node;
		current_node = current_node->next;
	}

	return (0);
}

/**
 * free_list - Free the memory allocated for the list.
 * @head_ptr: A pointer to the head of the list.
 */
void free_list(list_t **head_ptr)
{
	list_t *current_node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}

	head = *head_ptr;
	current_node = head;

	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}

	*head_ptr = NULL;
}


