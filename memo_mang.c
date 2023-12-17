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
	unsigned char *old_ptr, *new_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		result = malloc(new_size);
		if (result == NULL)
			return (NULL);
		return (result);
	}
	if (!new_size && ptr)
	{
		free(ptr);
		return (NULL);
	}
	old_ptr = (unsigned char *)ptr;
	result = malloc(new_size);
	if (result == NULL)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (unsigned char *)result;
	for (i = 0; i < old_size && i < new_size; i++)
		new_ptr[i] = *old_ptr++;
	free(ptr);
	return (result);
}

/**
 * ma_memcpy - copy n bytes of memory from src to dst
 * @dst: destination pointer
 * @src: source pointer
 * @n: the size in bytes to be copied
 * Return: pointer to new pointer
 */
char *ma_memcpy(char *dst, const char *src, unsigned int n)
{
	unsigned int i;

	char *ret = dst;

	for (i = 0; i < n; i++)
	{
		*dst++ = *src++;
	}
	return (dst);
}

/**
 * deallocate - free allocated memory for array pointer and user input
 * @argus: array of pointer to the character
 */
void deallocate(char **argus)
{
	int i;

	for (i = 0; argus[i] != NULL; i++)
	{
		free(argus[i]);
	}
	free(argus);
}

/**
 * deallocate_env - deallocate memory allocated for ma_setenv
 */
void deallocate_env(void)
{
	int i;

	for (i = 0; i < num_p && env_n[i] != NULL; ++i)
		free(env_n[i]);
}

/**
 * sweep_all - free allocated memory for all malloc
 * @argus: array of pointer to the character
 */
void sweep_all(char **argus)
{
	deallocate(argus);
	if (usrin)
		free(usrin);
}
