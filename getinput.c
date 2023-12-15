#include "shell.h"

/**
 * get_process_stdininput - gets input from stdin and leads it to next process
 *
 * Return: status of the user input
 */
int get_process_stdininput(void)
{
	int count = 0, loca_count = 0, stat = 0;
	size_t n = 0;
	char *usrin = NULL, c;

	do {
		c = ma_getline(&usrin, &n, STDIN_FILENO);
		source = 0;
		replflag = 0;
		if (usrin[c - 1] == '\n')
			(usrin[c - 1] = '0');
		count++;
		loca_count++;
<<<<<<< HEAD
		replfalg = 0;
		stat = ma_separat(usrin);
=======
		{
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
>>>>>>> 97098e3ee2d2c4936091a6f0d64339980b548c8b
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
	deallocate_env();
	exit(stat);
}

/**
 * ma_readprocess_execute_file- read input from a file take as
 * a command line argument
 * @filename: source of the file to be read
 * Return: 0 on success
 */
void ma_readprocess_execute_file(const char *filename)
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

	while ((ma_getline(&line, &n, fd)) != -1)
	{
		count++;
		loca_count++;
		source = 0;
		replflag = 0;
		stat = ma_parser(line);
	}
	if (line)
		free(line);
	close(fd);
	exit(stat);
}
