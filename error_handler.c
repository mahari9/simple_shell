#include "shell.h"

/**
 * display_error - Function that prints error message for code error 127
 * @argv: vector argument
 * @argus:  Array of pointers to the command line arguments
 * return: error message or NULL
 */
char *display_error(char **argv, char **argus)
{
	int length;
	char *error, *ec;

	ec = ma_itoa(count);
	if (!ec)
		return (NULL);
	length = ma_strlen(argv[0]) + ma_strlen(ec) + ma_strlen(argus[0]);
	error = malloc(sizeof(char) * (length + 17));
	if (!error)
	{
		free(ec);
		return (NULL);
	}
	ma_strcpy(error, argv[0]);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, ": ");
	ma_strcat(error, argus[0]);
	ma_strcat(error, ": not found\n");
	free(ec);
	WRT(error);
	free(argus);
	free(error);
	return (error);
}

/**
 * display_error126 - Function that prints error message for code error 126
 *  @argv: vector argument
 * @argus: Array of pointers to the command line arguments
 * Return: error message
 */
char *display_error126(char **argv, char **argus)
{
	int length;
	char *error, *ec;

	ec = ma_itoa(count);
	if (!ec)
		return (NULL);
	length = ma_strlen(argv[0]) + ma_strlen(ec) + ma_strlen(argus[0]);
	error = malloc(sizeof(char) * (length + 25));
	if (!error)
	{
		free(ec);
		return (NULL);
	}
	ma_strcpy(error, argv[0]);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, ": ");
	ma_strcat(error, argus[0]);
	ma_strcat(error, ": permission denied\n");
	free(ec);
	WRT(error);
	free(argus[0]);
	free(error);
	return (error);
}

/**
 * display_errorexit - Function that prints error message for invalid exit
 * @argv: arguments vector
 * @argus: array of Pointer to command line arguments
 * Return: Nothing
 */
void display_errorexit(char **argv, char **argus)
{
	int length;
	char *error, *ec;

	ec = ma_itoa(count);
	if (!ec)
		return;
	length = ma_strlen(argv[0]) + ma_strlen(ec) + ma_strlen(argus[1] + 4);
	error = malloc(sizeof(char) * (length + 24));
	if (!error)
	{
		free(ec);
		return;
	}
	ma_strcpy(error, argv[0]);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, ": ");
	ma_strcat(error, argus[0]);
	ma_strcat(error, ": invalid number: ");
	ma_strcat(error, argus[1]);
	ma_strcat(error, "\n");
	free(ec);
	WRT(error);
	free(argus);
	free(error);
}

/**
 * ma_cd_error - can't change current directory to specified location
 * @argv: vector arguments
 * @argus: Array of pointers to the command line arguments
 * Return: error message
 */

char *ma_cd_error(char **argv, char **argus)
{
	char *errmsg, *error, *ec;
	int length;

	ec = ma_itoa(count);
	if (!ec)
		return (NULL);
	errmsg = ": cd: Unable to change directory to ";
	length = ma_strlen(argv[0]) + ma_strlen(ec) +
		ma_strlen(errmsg) + ma_strlen(argus[1] + 4);
	error = malloc(sizeof(char) * length);
	if (!error)
	{
		ma_perror(NULL, NULL, 12);
		free(ec);
		return (NULL);
	}
	ma_strcpy(error, argv[0]);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, errmsg);
	ma_strcat(error, argus[1]);
	ma_strcat(error, "\n");
	ma_strcat(error, "\0");
	free(ec);
	return (error);
}
