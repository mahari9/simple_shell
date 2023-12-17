#include "shel.h"

/**
 * separator - Separates command recieved from stdin by ;
 * @usri: String gathered from stdin
 * Return: Parsed strings to be used as commands
 */
char **separator(char *usri)
{
	char **argus;
	char **argu;
	int i;
	int buffsize = BUFFMAXSIZE;

	if (usri[0] == ' ' && usri[ma_strlen(usri)] == ' ')
		exit(0);
	if (usri == NULL)
		return (NULL);
	argus = malloc(sizeof(char *) * buffsize);
	if (!argus)
	{
		free(argus);
		perror("memory allocation failure");
		return (NULL);
	}
	argu = strtok(usri, ";");
	for (i = 0; argu; i++)
	{
		argus[i] = argu;
		argu = strtok(NULL, ";");
	}
	argus[i] = NULL;

	return (argus);
}
