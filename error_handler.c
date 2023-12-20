#include "shell.h"

/**
 * display_error - Function that prints error message for code error 127
 * @argus: Array of pointers to the command line arguments
 * Return: Error message or NULL
 */
char *display_error(char **argus)
{
	int length;
	char *error, *ec;
	
	if (count !=0)
	{
		ec = ma_itoa(count);
		if (!ec)
			return (NULL);
	}
	else
		ec = "0";
	length = ma_strlen(shell) + ma_strlen(ec) + ma_strlen(argus[0]) + 17;
	error = (char*)malloc(sizeof(char) * length);
	if (!error)
	{
		free(ec);
		return (NULL);
	}

	ma_strcpy(error, shell);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, ": ");
	ma_strcat(error, argus[0]);
	ma_strcat(error, ": not found\n");

	if (count)
		free(ec);
	return (error);
}


/**
 * display_error126 - Function that prints error message for code error 126
 * @argus: Array of pointers to the command line arguments
 * Return: error message
 */
char *display_error126(char **argus)
{
	int length;
	char *error, *ec;
	
	if (count != 0)
	{
		ec = ma_itoa(count);
		if (!ec)
			return (NULL);
	}
	else
		ec = "0";
	length = ma_strlen(shell) + ma_strlen(ec) + ma_strlen(argus[0]);
	error = (char*)malloc(sizeof(char) * (length + 25));
	if (!error)
	{
		free(ec);
		return (NULL);
	}
	ma_strcpy(error, shell);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, ": ");
	ma_strcat(error, argus[0]);
	ma_strcat(error, ": permission denied\n");

	if (count)
		free(ec);
	return (error);
}

/**
 * display_errorexit - Function that prints error message for invalid exit
 * @argus: array of pointers to the  command line arguments
 * Return: Nothing
 */
void display_errorexit(char **argus)
{
	int length;
	char *error, *ec;

	ec = ma_itoa(count);
	if (!ec)
		return;
	length = ma_strlen(shell) + ma_strlen(ec) + ma_strlen(argus[1] + 4);
	error = (char*)malloc(sizeof(char) * (length + 24));
	if (!error)
	{
		free(ec);
		return;
	}
	ma_strcpy(error, shell);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, ": ");
	ma_strcat(error, argus[0]);
	ma_strcat(error, ": invalid number: ");
	ma_strcat(error, argus[1]);
	ma_strcat(error, "\n");
	
	free(ec);
	WRT(error);
	free(error);
}

/**
 * ma_cd_error - can't change current directory to specified location
 * @argus: pointers to the command line arguments
 * Return: error message
 */

char *ma_cd_error(char *argus)
{
	char *errmsg, *error, *ec;
	int length;

	ec = ma_itoa(count);
	if (!ec)
		return (NULL);
	errmsg = ": cd: Unable to change directory to ";
	length = ma_strlen(shell) + ma_strlen(ec) +
		ma_strlen(errmsg) + ma_strlen(argus) + 4;
	error = malloc(sizeof(char) * length);
	if (!error)
	{
		free(ec);
		return (NULL);
	}
	ma_strcpy(error, shell);
	ma_strcat(error, ": ");
	ma_strcat(error, ec);
	ma_strcat(error, errmsg);
	ma_strcat(error, (argus));
	ma_strcat(error, "\n");

	free(ec);
	return (error);
}
