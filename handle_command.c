#include "shell.h"

/**
 * handle_opera - handles when first operator is either && or ||
 * @usrin: input line to be tokenized
 * @opr: logical operator to be handled
 * Return: 0 on success
 */
int handle_opera(char *usrin, char *opr)
{
	int result = 0;
	char *cmnd, *log_and = ma_strstr(usrin, "&&");
	char *log_or = ma_strstr(usrin, "||");

	cmnd = ma_strtok(usrin, opr);
	while (cmnd != NULL)
	{
		result = ma_parser(cmnd);
		if (((result == 0) && (ma_strcmp(opr, "||") == 0))
				|| ((result != 0) && (ma_strcmp(opr, "&&") == 0)))
			return (result);
		log_or = ma_strstr(usrin, "||");
		log_and = ma_strstr(usrin, "&&");
		if (log_or == NULL || log_and < log_or)
			opr = "&";
		else
			opr = "|";
		cmnd = ma_strtok(NULL, opr);
	}
	return (result);
}

/**
 * ma_separat - separate given input into commands
 * @usrin: input of a line of string
 * Return: 0 on success
 */
int ma_separat(char *usrin)
{
	char *log_and, *log_or, *cmnd;
	int stat = 0;

	if (usrin[0] == ' ' && usrin[ma_strlen(usrin)] == ' ')
		exit(0);
	if (!usrin)
		return (0);
	cmnd = ma_strtok(usrin, ";");
	for (; cmnd != NULL;)
	{
		log_and = ma_strstr(cmnd, "&&");
		log_or = ma_strstr(cmnd, "||");
		if (log_and && (log_or == NULL || log_and < log_or))
			stat = handle_opera(cmnd, "&&");
		else if (log_or && (log_and == NULL || log_or < log_and))
			stat = handle_opera(cmnd, "||");
		else
			stat = ma_parser(cmnd);
		cmnd = ma_strtok(NULL, ";");
	}
	return (stat);
}
/**
 * ma_parser - splits line into an array of tokens
 * @usrin: input command-line to be splited in arguments
 *
 * Return: 0 on seccuss -1 on failure
 */
int *ma_parser(char *usrin)
{
	int i, stat = 0;
	const char *delim = " \n\t&|";
	char *usrin_copy = NULL, *argu, **argus, **argv, *found;

	usrin_copy = ma_strdup(usrin);
	if (usrin_copy != NULL)
	{
		argu = ma_strtok(usrin_copy, delim);
		for (i = 0; argu != NULL; i++)
			argu = ma_strtok(NULL, delim);
		free(usrin_copy);
	}
	else
		return (-1);
	argus = malloc(sizeof(char *) * (i + 1));
	if (!argus)
		return (ma_perror(NULL, NULL, NULL, 12));
	argu = ma_strtok(usrin, delim);
	for (i = 0; argu != NULL; i++)
	{
		argus[i] = ma_strdup(argu);
		found = impl_var(argus[i]);
		if (found)
		{
			free(argus[i]);
			argus[i] = found;
		}
		argu = ma_strtok_(NULL, delim);
	}
	argus[i] = NULL;
	if (replflag == 0)
		stat = execute_commands(argus,  argv);
	else
		write(STDOUT_FILENO, "\n", 1);
	deallocate(argus, NULL);
	return (stat);
}

/**
 * handle_commands - Function that handles execution of different commands
 * @argv: argument vector
 * @argus: Array of pointers to command line arguments passed to function
 * Return: 0 on success
 */
int handle_commands(char **argus, char **argv)
{
	char **envm = environ, *found, *usrin, *line;
	int i = 0, stat = 0;

	while (argus[i] != NULL)
	{
		found = search_alias(argus[i], NULL);
		if (found && (ma_strcmp(argus[0], "alias") != 0))
		{
			free(argus[i]);
			argus[i] = ma_strdup(found);
		}
		i++;
	}
	if (argus && argus[0])
	{
		stat = execute_builtin(argus);
		if (stat != 1)
			return (stat);
		if (isatty(STDIN_FILENO))
			return (external_command(argus, usrin, argv, envm));
		else
			return (external_command(argus, line, argv, envm));
	}
	return (0);
}
