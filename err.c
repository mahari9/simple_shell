#include "shel.h"

/**
 * ma_perror - handle error message to standard output
 * @argus: array of pointers to the arguments
 * @count: ...
 * @argv:....
 * @cod: code of errore
 *
 * Return: error code
 */
int ma_perror(char **argus, int count, char **argv, int cod)
{
	int stat = 0;
	char *error = NULL;

	if (cod == 22)
	{
		write(STDERR_FILENO, "Invalid Argument\n", 17);
		errno = EINVAL;
		stat = -1;
	}
	else if (cod == 126)
	{
		error = display_error126(argus, count, argv);
		WRT(error);
		stat = 126;
	}
	else if (cod == 127)
	{
		error = display_error(argus, count, argv);
		WRT(error);
		stat = 127;
	}
	else if (cod == 12)
	{
		write(STDERR_FILENO, "Error: Unable to allocate memory\n", 33);
		stat = -1;
	}

	if (error)
	{
		WRT(error);
		free(error);
	}
	return (stat);
}
