#include "shell.h"

/**
 * handle_opera - handles when first operator is either && or ||
 * @cmd: input command  to be tokenized
 * @opr: logical operator to be handled
 * Return: 0 on success
 */
int handle_opera(char *cmd, char *opr)
{
	int result = 0;
	char *cmnd, *log_and = ma_strstr(usrin, "&&");
	char *log_or = ma_strstr(usrin, "||");

	cmnd = ma_strtok(cmd, opr);
	while (cmnd != NULL)
	{
		result = ma_parser(cmnd);
		if (((result == 0) && (ma_strcmp(opr, "||") == 0))
				|| ((result != 0) && (ma_strcmp(opr, "&&") == 0)))
			return (result);
		log_or = ma_strstr(cmd, "||");
		log_and = ma_strstr(cmd, "&&");
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
 * @usri: input of a line of string
 * Return: 0 on success
 */
int ma_separat(char *usri)
{
	char *log_and, *log_or, *cmnd;
	int stat = 0;

	usri = hashtag_comm(usri);
	if (usri[0] == ' ' && usri[ma_strlen(usri)] == ' ')
		exit(0);
	if (!usri)
		return (0);
	cmnd = ma_strtok(usri, ";");
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
 * @usri: input command-line to be splited in arguments
 *
 * Return: 0 on seccuss -1 on failure
 */
int ma_parser(char *usri)
{
	int i, stat = 0;
	const char *delim = " \n\t&|";
	char *usrin_copy = NULL, *argu, **argus, *found;
	char *usri_copy = NULL, *argu, **argus, *found;

	usri_copy = ma_strdup(usri);
	if (usri_copy != NULL)
	{
		argu = ma_strtok(usri_copy, delim);
		for (i = 0; argu != NULL; i++)
			argu = ma_strtok(NULL, delim);
		free(usri_copy);
	}
	else
		return (-1);
	argus = malloc(sizeof(char *) * (i + 1));
	if (!argus)
		return (ma_perror(NULL, NULL, 12));
	argu = ma_strtok(usri, delim);
	for (i = 0; argu != NULL; i++)
	{
		argus[i] = ma_strdup(argu);
		found = impl_var(argus[i]);
		if (found)
		{
			free(argus[i]);
			argus[i] = found;
		}
		argu = ma_strtok(NULL, delim);
	}
	argus[i] = NULL;
	if (replflag == 0)
		stat = handle_commands(argus, NULL);
		stat = handle_commands(argus);
	else
		write(STDOUT_FILENO, "\n", 1);
	deallocate(argus, NULL);
	return (stat);
}

/**
 * handle_commands - Function that handles execution of different commands
 * @argus: Array of pointers to command line arguments passed to function
 * @argv: vector argument
 * Return: 0 on success
 */
int handle_commands(char **argus)
{
	char **envm = environ, *found;
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
		else
			return (inputcommand_execute(argv, envm));
	}
	return (0);
}
