#include "shell.h"

/**
 * ma_readprocess_execute_file- read input from a file take as
 * a command line argument
 * @filename: source of the file to be read
 * Return: 0 on success
 */
void ma_readprocess_execute_file(const char *filename)
{
	char *line = NULL, **envm;
	size_t n = 0;
	ssize_t c;
	int loca_count, status = 0, fd;

	if (!filename)
		return;
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
			line[c - 1] = '\0';
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
		status = ma_separat(line);
	}
	if (line)
		free(line);
	deallocate_env();
	close(fd);
	exit(status);
}
