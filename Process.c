#include "shell.h"
/**
 * get_process_stdininput - gets input from stdin and leads it to next process
 * Return: status of the user input
 */
int get_process_stdininput(void)
{
	int loca_count = 0, status = 1;
	size_t n = 0;
	ssize_t c;
	char **envm;

	usrin = NULL;
	if (isatty(STDIN_FILENO))
		display_prompt();
	while ((c = ma_getline(&usrin, &n, STDIN_FILENO)) != -1)
	{
		source = 0;
		replflag = 0;
		no_pth = 1;
		if (usrin[c - 1] == '\n')
			usrin[c - 1] = '\0';
		loca_count++;
		count++;
		for (envm = environ; *envm; ++envm)
		{
			if (ma_strcmp(*envm, "PATH=") == 0)
			{
				no_pth = 0;
				break;
			}
		}
		status = ma_separat(usrin);
		if (isatty(STDIN_FILENO))
		{
			display_prompt();
			fflush(stdout);
		}
	}
	if (usrin)
		free(usrin);
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "\n", 2);
	deallocate_env();
	exit(status);
}

/**
 * ma_parser - splits line into an array of tokens
 * @usri: input command-line to be splited in arguments
 *
 * Return: 0 on seccuss -1 on failure
 */
int ma_parser(char *usri)
{
	int i, status = 0;
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
	argus = malloc(sizeof(char *) * (i + 1));
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
		status = handle_commands(argus);
	else
		write(STDOUT_FILENO, "\n", 1);
	deallocate(argus);
	return (status);
}
/**
 * ma_separat - separates multiple cmnds
 * @line: line to be split
 *
 * Return: 0
 */
int ma_separat(char *line)
{
	char *csav, *and_tok, *or_tok, *cmnds;
	int status = 0;

	line = hashtag_comm(line);
	if (!line)
		return (0);
	cmnds = ma_strtok_r(line, ";", &csav);
	for (; cmnds != NULL;)
	{
		and_tok = ma_strstr(cmnds, "&&");
		or_tok = ma_strstr(cmnds, "||");
		if (and_tok && (or_tok == NULL || and_tok < or_tok))
			status = log_and(cmnds);
		else if (or_tok && (and_tok == NULL || or_tok < and_tok))
			status = log_or(cmnds);
		else
			status = ma_parser(cmnds);
		cmnds = ma_strtok_r(NULL, ";", &csav);
	}
	return (status);
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
