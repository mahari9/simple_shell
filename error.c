#include "shel.h"

/**
 * ma_perror - handle error message to standard output
 * @argus: array of pointers to the arguments
 * @cod: code of errore
 *
 * Return: error code
 */
int ma_perror(char **argus, int cod)
{
	int status = 0;
	char *error = NULL;

	if (cod == 22)
	{
		write(STDERR_FILENO, "Invalid Argument\n", 17);
		errno = EINVAL;
		status = -1;
	}
	else if (cod == 126)
	{
		error = display_error126(argus);
		WRT(error);
		status = 126;
	}
	else if (cod == 127)
	{
		error = display_error(argus);
		WRT(error);
		status = 127;
	}
	else if (cod == 12)
	{
		write(STDERR_FILENO, "Error: Unable to allocate memory\n", 33);
		status = -1;
	}

	if (error)
	{
		WRT(error);
		free(error);
	}
	return (status);
}
