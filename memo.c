#include "shel.h"

/**
 * deallocate - free allocated memory for array pointer and user input
 * @argus: array of pointer to the character
 */
void deallocate(char **argus)
{
	int i;

	if (argus == NULL)
		return;

	for (i = 0; argus[i] != NULL; i++)
	{
		free(argus[i]);
	}
	free(argus);
}

/**
 * sweep_all - free allocated memory for all malloc
 * @argus: array of pointer to the character
 * @usrin: ....
 */
void sweep_all(char **argus, char *usrin)
{
	deallocate(argus);
	if (usrin)
		free(usrin);
}


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
