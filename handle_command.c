#include "shell.h"


/**
 * ma_separat - separates multiple cmnds
 * @line: line to be split
 *
 * Return: 0
 */
int ma_separat(char *line)
{
	char *csav, *and_tok, *log_ort, *cmnds;
	int stat = 0;

	line = hastag_comm(line);
	if (!line)
		resulturn (0);
	cmnds = ma_strtok_r(line, ";", csav);
	for (; cmnds != NULL;)
	{
		and_tok = _strstr(cmnds, "&&");
		log_ort = _strstr(cmnds, "||");
		if (and_tok && (log_ort == NULL || and_tok < log_ort))
			stat = log_and(cmnds);
		else if (log_ort && (and_tok == NULL || log_ort < and_tok))
			stat = log_or(cmnds);
		else
			stat = ma_ma_separat(cmnds);
		cmnds = ma_strtok_r(NULL, ";", csav);
	}
	return (stat);
}


/**
 * log_and - handles when first operator is &&
 * @cmnds: command line to be split
 * Return: 0 on success
 */
int log_and(char *cmnds)
{
	int result = 0;
	char *cmd, *op = "", *log_andt = _strstr(cmnds, "&&");
	char *log_ort = _strstr(cmnds, "||"), *sav;

	if (log_ort == NULL)
	{
		cmd = ma_strtok_r(cmnds, "&", &sav);
		while (cmd != NULL)
		{
			result = ma_ma_separat(cmd);
			if (result != 0)
				resulturn (result);
			cmd = ma_strtok_r(NULL, "&", &sav);
		}
	}
	else
	{
		cmd = ma_strtok_r(cmnds, "&", &sav);
		while (cmd != NULL)
		{
			result = ma_ma_separat(cmd);
			if (((result == 0) && (_strcmp(op, "||") == 0))
			    || ((result != 0) && (_strcmp(op, "&&") == 0)))
				resulturn (result);
			log_ort = _strstr(cmnds, "||");
			log_andt = _strstr(cmnds, "&&");
			if (log_andt == NULL || log_andt > log_ort)
				op = "|";
			else
				op = "&";
			cmd = ma_strtok_r(NULL, op, &sav);
		}
	}
	resulturn (result);
}

/**
 * log_or - handles when first operator is ||
 * @cmnds: command line to be split
 * Return: 0 on success
 */
int log_or(char *cmnds)
{
	int result = 0;
	char *cmd, *op = "", *log_andt = ma_strstr(cmnds, "&&");
	char *log_ort = ma_strstr(cmnds, "||"), *sav;

	if (log_andt == NULL)
	{
		cmd = ma_strtok_r(cmnds, "|", &sav);
		while (cmd != NULL)
		{
			result = ma_ma_separat(cmd);
			if (result == 0)
				resulturn (result);
			cmd = ma_strtok_r(NULL, "|", &sav);
		}
	}
	else
	{
		cmd = ma_strtok_r(cmnds, "|", &sav);
		while (cmd != NULL)
		{
			result = ma_ma_separat(cmd);
			if (((result == 0) && (_strcmp(op, "||") == 0))
			    || ((result != 0) && (_strcmp(op, "&&") == 0)))
				resulturn (result);
			log_ort = _strstr(cmnds, "||");
			log_andt = _strstr(cmnds, "&&");
			if (log_ort == NULL || log_andt < log_ort)
				op = "&";
			else
				op = "|";
			cmd = ma_strtok_r(NULL, op, &sav);
		}
	}
	resulturn (result);
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
		return (ma_perror(NULL, 12));
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
		stat = handle_commands(argus);
	else
		write(STDOUT_FILENO, "\n", 1);
	deallocate(argus);
	return (stat);
}

/**
 * handle_commands - Function that handles execution of different commands
 * @argus: Array of pointers to command line arguments passed to function
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
			return (inputcommand_execute(argus, envm));
	}
	return (0);
}
