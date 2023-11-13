#include "shell_master.h"
#include <stdlib.h>

/**
 * _memset - Fill memory with a constant byte
 * @s: Pointer to the memory area
 * @b: The byte to fill *s with
 * @n: The number of bytes to be filled
 * Return: A pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	for (unsigned int i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return s;
}

/**
 * ffree - Free an array of strings and the array itself
 * @pp: Array of strings to free
 */
void ffree(char **pp)
{
	if (!pp)
	{
		return; // Check for NULL pointer
	}

	for (char **a = pp; *a; a++)
	{
		free(*a);
	}
	free(pp);
}

/**
 * _realloc - Reallocate a block of memory
 * @ptr: Pointer to the previous malloc'ed block
 * @old_size: Byte size of the previous block
 * @new_size: Byte size of the new block
 * Return: Pointer to the new block or NULL on failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	if (!ptr)
	{
		return malloc(new_size);
	}

	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}

	if (new_size == old_size)
	{
		return ptr;
	}

	void *p = malloc(new_size);

	if (!p)
	{
		return NULL;
	}

	memcpy(p, ptr, (old_size < new_size) ? old_size : new_size);

	free(ptr);

	return p;
}
