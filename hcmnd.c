#include "shel.h"

/**
 * ma_parser - splits line into an array of tokens
 * @usri: input command-line to be splited in arguments
 *
 * Return: 0 on seccuss -1 on failure
 */
char **ma_parser(char *usri)
{
        int i;
        const char *delim = " \n\t";
        char *usri_copy = NULL, *argu, **argus;

        usri_copy = ma_strdup(usri);
        if (usri_copy != NULL)
        {
                argu = strtok(usri_copy, delim);
                for (i = 0; argu != NULL; i++)
                        argu = strtok(NULL, delim);
                free(usri_copy);
        }
        else
                return (NULL);
        argus = (char **)malloc(sizeof(char *) * (i + 1));
        if (!argus)
	{
		perror("memory allocation failure");
		deallocate(argus);
		return (NULL);
	}       
        argu = strtok(usri, delim);
        for (i = 0; argu != NULL; i++)
        {
                argus[i] = ma_strdup(argu);
                argu = strtok(NULL, delim);
        }
        argus[i] = NULL;
	free(usri_copy);
        return (argus);
}
