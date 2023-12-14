#include "shell.h"

/**
 * ma_perror_cd  - write error message for failure to  cd to specified location
 * @argus: pointer to user input command
 * @cod: code of error
 */
void ma_perror_cd(char **argv, char **argus, int cod)
{
	char *error = NULL;

	if (cod == 2)
	{
		error = ma_cd_error(argv, argus);
		status = 2;
	}

	if (error)
	{
		WRT(error);
		free(error);
	}
}

/**
 * ma_perror - Handle error message to standard output
 * @argv: argument vector
 * @argus: Array of pointers to the arguments
 * @cod: code of errore
 *
 * Return: error code
 */
int ma_perror(argv, argus, int cod)
{
	int status = 0;
	char *error = NULL;

	if (cod == 22)
	{
		error = "Invalid Argument\n"
			WRT(error);
		errno = EINVAL;
		status = -1;
	}
	else if (cod == 126)
	{
		error = display_error126(argv, argus);
		WRT(error);
		status = 126;
	}
	else if (cod == 127)
	{
		error = display_error(argv, argus);
		WRT(error);
		status = 127;
	}
	else if (cod == 12)
	{
		error = "Error: Unable to allocate memory\n";
		WRT(error);
		status = -1;
	}

	if (error)
	{
		WRT(error);
		free(error);
	}
	return (status);
}

/**
 * ma_perrorfile - write error message for file of unable to open
 * @argv: array pointers to the command line arguments
 */
void ma_perrorfile(char **argv)
{
	char *error, *ec, *msg = ": Can't open ",
		int len, status;

	if (count != 0)
	{
		ec = ma_itoa(count);
		if (!ec)
			return;
	}
	else
		ec = "0";

	len = ma_strlen(argv[0]) + ma_strlen(ec) + ma_strlen(argv[1])
		+ ma_strlen(msg) + 4;
	error = malloc(sizeof(char) * (len));
	if (!error)
	{
		if (count)
			free(ec);
		return;
	}

	ma_strcpy(error, argv[0]);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, msg);
	ma_strcat(error, argv[1]);
	ma_strcat(error, "\n");

	if (count)
		free(ec);
	WRT(error);
	free(error);
	status = 127;
	exit(status);
}
