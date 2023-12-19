#include "shell.h"

/**
 * ma_separat - separates multiple cmnds
 * @line: line to be split
 *
 * Return: 0
 */
int ma_separat(char *line)
{
	char *csav, *and_tok, *or_tok, *cmnds;
	int stat = 0;

	line = hashtag_comm(line);
	if (!line)
		return (0);
	cmnds = ma_strtok_r(line, ";", &csav);
	for (; cmnds != NULL;)
	{
		and_tok = ma_strstr(cmnds, "&&");
		or_tok = ma_strstr(cmnds, "||");
		if (and_tok && (or_tok == NULL || and_tok < or_tok))
			stat = log_and(cmnds);
		else if (or_tok && (and_tok == NULL || or_tok < and_tok))
			stat = log_or(cmnds);
		else
			stat = ma_parser(cmnds);
		cmnds = ma_strtok_r(NULL, ";", &csav);
	}
	return (stat);
}


/**
 * log_and - logical and handler when first operator is and
 * @cmnds: command line to be split
 * Return: 0 on success
 */
int log_and(char *cmnds)
{
	int result = 0;
	char *cmd, *opr = "", *and_tok = ma_strstr(cmnds, "&&");
	char *or_tok = ma_strstr(cmnds, "||"), *sav;

	if (or_tok == NULL)
	{
		cmd = ma_strtok_r(cmnds, "&", &sav);
		while (cmd != NULL)
		{
			result = ma_parser(cmd);
			if (result != 0)
				return (result);
			cmd = ma_strtok_r(NULL, "&", &sav);
		}
	}
	else
	{
		cmd = ma_strtok_r(cmnds, "&", &sav);
		while (cmd != NULL)
		{
			result = ma_parser(cmd);
			if (((result == 0) && (ma_strcmp(opr, "||") == 0))
			    || ((result != 0) && (ma_strcmp(opr, "&&") == 0)))
				return (result);
			or_tok = ma_strstr(cmnds, "||");
			and_tok = ma_strstr(cmnds, "&&");
			if (and_tok == NULL || and_tok > or_tok)
				opr = "|";
			else
				opr = "&";
			cmd = ma_strtok_r(NULL, opr, &sav);
		}
	}
	return (result);
}

/**
 * log_or - logical or handler  when first operator is or
 * @cmnds: command line to be split
 * Return: 0 on success
 */
int log_or(char *cmnds)
{
	int result = 0;
	char *cmd, *opr = "", *and_tok = ma_strstr(cmnds, "&&");
	char *or_tok = ma_strstr(cmnds, "||"), *sav;

	if (and_tok == NULL)
	{
		cmd = ma_strtok_r(cmnds, "|", &sav);
		while (cmd != NULL)
		{
			result = ma_parser(cmd);
			if (result == 0)
				return (result);
			cmd = ma_strtok_r(NULL, "|", &sav);
		}
	}
	else
	{
		cmd = ma_strtok_r(cmnds, "|", &sav);
		while (cmd != NULL)
		{
			result = ma_parser(cmd);
			if (((result == 0) && (ma_strcmp(opr, "||") == 0))
			    || ((result != 0) && (ma_strcmp(opr, "&&") == 0)))
				return (result);
			or_tok = ma_strstr(cmnds, "||");
			and_tok = ma_strstr(cmnds, "&&");
			if (or_tok == NULL || and_tok < or_tok)
				opr = "&";
			else
				opr = "|";
			cmd = ma_strtok_r(NULL, opr, &sav);
		}
	}
	return (result);
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
	char *usri_copy = NULL, *argu, **argus, *found, *sav;

	usri_copy = ma_strdup(usri);
	if (usri_copy != NULL)
	{
		argu = ma_strtok_r(usri_copy, delim, &sav);
		for (i = 0; argu != NULL; i++)
			argu = ma_strtok_r(NULL, delim, &sav);
		free(usri_copy);
	}
	else
		return (-1);
	argus = (char**)malloc(sizeof(char *) * (i + 1));
	if (!argus)
		return (ma_perror(NULL, 12));
	argu = ma_strtok_r(usri, delim, &sav);
	for (i = 0; argu != NULL; i++)
	{
		argus[i] = ma_strdup(argu);
		found = impl_var(argus[i]);
		if (found)
		{
			free(argus[i]);
			argus[i] = found;
		}
		argu = ma_strtok_r(NULL, delim, &sav);
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
