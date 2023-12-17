#include "shel.h"

/**
 * main - Input piont to the program
 * @argc: The integral values of the number of cmd_line arguments
 * @argv: An array of pointers that store the cmd_line arguments
 * Return: Alway 0
 */
int main(int argc, char **argv)
{
	int loca_count = 0, stat = 0, i;
	size_t n = 0;
	char **argu, **argus, *usrin = NULL, c, **envm;

	count = 0;
	status = 0;
	shell = argv[0];
	(void) argc;

	if (isatty(STDIN_FILENO))
		display_prompt();
	do {
		c = getline(&usrin, &n, STDIN_FILENO);
		source = 0;
		no_pth = 1;
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
		argus = separator(usrin);
		for (i = 0; argus[i] != NULL; i++)
		{
			argu = ma_parser(argus[i]);
			if (ma_strcmp(argu[0], "exit") == 0)
			{
				free(argus);
				exit_shell(argu);
			}
			if (ma_strcmp(argu[0], "env") == 0)
			{
				stat = (ma_env(environ));
				free(argu);
			}
			else
			{
				stat = (inputcommand_execute(argu, envm));
				free(argu);
			}
		}
		if (isatty(STDIN_FILENO))
		{
			display_prompt();
			fflush(stdout);
		}
	} while (1);
	if (usrin)
		free(usrin);
	deallocate(argus);
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "\n", 2);
	return (stat);
}
