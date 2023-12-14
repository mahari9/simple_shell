#include "shell.h"

/**
 * get_process_stdininput - gets input from stdin and leads it to next process
 *
 * Return: status of the user input
 */
int get_process_stdininput(void)
{
	int count = 0, loca_count = 0, stat = 0;
	char *usrin = NULL, **envm;

	do {
		count++;
		usrin = ma_getline();
		if (usrin[0] == '0')
			continue;
		loca_count++;
		replfalg = 0;
		hist(usrin);
		for (envm = environ; *envm; ++envm)
		{
			if (ma_strcmp(*envm, "PATH=") == 0)
			{
				path_unset = 0;
				break;
			}
		}
		stat = ma_separat(usrin);
		if (isatty(STDIN_FILENO))
		{
			display_prompt();
			fflush(stdout);
		}
	} while (1);
	if (usrin)
		free(usrin);
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "\n", 2);
	deallocate_env(void);
	exit(stat);
}

/**
 * ma_readprocess_execute_file - read input from a file take as
 * a command line argument
 * @filename: source of the file to be read
 * @argv: arguments vector
 * Return: 0 on success
 */
void ma_readprocess_execute_file(const char *filename, char **argv)
{
	char *line = NULL;
	size_t n = 0;
	int count = 0, loca_count, stat = 0, fd;

	if (!filename)
		exit(EXIT_FAILURE);
	fd =  open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Can't open file");
		exit(EXIT_FAILURE);
	}

	while ((getline(&line, &n, fd)) != -1)
	{
		count++;
		loca_count++;
		status = ma_parser(line);
	}
	if (line)
		free(line);
	close(filename);
	exit(stat);
}
