#include "shell.h"

/**
 * ma_realloc - reallocates a memory block
 * @ptr: pointer
 * @old_size: previous size of the pointer
 * @new_size: new size of the pointer
 * Return: Pointer to the reallocated memory
 */
void *ma_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *result;
	char *old_ptr, *new_ptr;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		result = malloc(new_size);
		if (result == NULL)
		return (result);
	}
	if (new_size == 0 && ptr)
	{
		free(ptr);
	}
	old_ptr = ptr;
	result = malloc(sizeof(*old_ptr) * new_size);
	if (result == NULL)
		free(ptr);
	new_ptr = result;
	ma_memcpy(new_size, old_size);
	free(ptr);
	return (result);
}

/**
 * ma_memcpy - copy n bytes of memory from src to dst
 * @new_size: destination pointer
 * @old_size: source pointer
 * Return: pointer to new pointer
 */
void ma_memcpy(char *new_size, char *old_size)
{
	unsigned int i;
	void *nw_ptr, *od_ptr

	for (i = 0; i < old_size && i < new_size; i++)
		nw_ptr = *old_ptr++;
}
/**
 * deallocate - free allocated memory for array pointer and user input
 * @argus: array of pointer to the character
 * @usrin: pointer to character
 */
void deallocate(char **argus, char *usrin)
{
	free(argus);
	free(usrin);
	argus = NULL;
	usrin = NULL;
}

/**
 * deallocate_env - deallocate memory allocated for ma_setenv
 */
void deallocte_env(void)
{
	int i;

	for (i = 0; i < num_p && env_n[i] != NULL; ++i)
		free(env_n[i]);
}
