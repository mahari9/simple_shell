#include "shell.h"

/**
 * ma_perror_cd  - write error message for failure to  cd to specified location
 * @argus: pointer to user input command
 * @cod: code of error
 */
void ma_perror_cd(char *argus, int cod)
{
	char *error = NULL;

	if (cod == 2)
	{
		error = ma_cd_error(argus);
		if (error)
		{
			WRT(error);
			free(error);
		}
	}
}

/**
 * ma_perror - handle error message to standard output
 * @argv: array of pointers to the cmnd_line arguments
 * @cod: code of errore
 *
 * Return: error code
 */
int ma_perror(char **argv, int cod)
{
	int exit_status = 0;
	char *error = NULL;

	if (cod == 22)
	{
		write(STDERR_FILENO, "Invalid Argument\n", 17);
		errno = EINVAL;
		exit_status = -1;
	}
	else if (cod == 126)
	{
		error = display_error126(argv);
		exit_status = 126;
	}
	else if (cod == 127)
	{
		error = display_error(argv);
		exit_status = 127;
	}
	else if (cod == 12)
	{
		write(STDERR_FILENO, "Error: Unable to allocate memory\n", 33);
		exit_status = -1;
	}

	if (error)
	{
		WRT(error);
		free(error);
	}
	return (exit_status);
}

/**
 * ma_perrorfile - write error message for file of unable to open
 * @argv: array pointers to the command line arguments
 */
void ma_perrorfile(char **argv)
{
	char *error, *ec, *msg = ": Can't open ";
	int len;

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
	error = (char *)malloc(sizeof(char) * (len));
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
	exit_status = 127;
	exit(exit_status);
}
