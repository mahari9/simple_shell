#include "shell.h"

/**
 * main - Input piont to the program
 * @argc: The integral values of the number of cmd_line arguments
 * @argv: An array of pointers that store the cmd_line arguments
 * Return: Alway 0
 */
int main(int argc, char **argv)
{
	const char *filename;

	shell = argv[0];
	count = 0;
	num_p = 0;
	exit_status = 0;

	if (signal(SIGINT, signal_catcher) == SIG_ERR)
	{
		deallocate_env();
		exit(EXIT_FAILURE);
	}
	initialize_alias_count();
	if (argc == 2)
	{
		filename = argv[1];
		if (validate_file(filename))
			ma_readprocess_execute_file(filename);
		else
			ma_perrorfile(argv);
	}
	else
		get_process_stdininput();
	deallocate_env();
	(void)argc;
	return (0);
}
