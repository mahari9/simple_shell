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
	char *usrin = NULL, c, **envm;

	do {
		c = ma_getline(&usrin, &n, STDIN_FILENO);
		source = 0;
		no_pth = 1;
		replflag = 0;
		if (usrin[c - 1] == '\n')
			(usrin[c - 1] = '0');
		count++;
		loca_count++;
                for (envm = environ; *envm; ++envm)
                {
                        if (ma_strcmp(*envm, "PATH=") == 0)
                        {
                                no_pth = 0;
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
	char *line = NULL, c, **envm;
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

	while ((c = ma_getline(&line, &n, fd)) != -1)
	{
		source = 0;
		no_pth = 1;
		if (line[c - 1] == '\n')
			(line[c - 1] = '0');
		count++;
		loca_count++;
		for (envm = environ; *envm; ++envm)
		{
			if (ma_strcmp(*envm, "PATH=") == 0)
			{
				no_pth = 0;
				break;
			}
		}
		stat = ma_parser(line);
	}
	if (line)
		free(line);
	deallocate_env();
	close(fd);
	exit(stat);
}
