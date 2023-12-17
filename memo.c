#include "shel.h"

/**
 * deallocate - free allocated memory for array pointer and user input
 * @argus: array of pointer to the character
 */
void deallocate(char **argus)
{
	if (argus == NULL)
		return;

	for (int i = 0; argus[i] != NULL; i++)
	{
		free(argus[i]);
	}
	free(argus);
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
