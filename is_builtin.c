#include "shell.h"

/**
 * execute_builtin - Handles predefined built-in commands
 * @argus: Array pointers to the arguments passed to the program
 *
 * Return: -1 Failure 0 Success or 1 if not builtin.
 */
int execute_builtin(char **argus)
{

	if (ma_strncmp(argus[0], "exit", 4) == 0)
	{
		return (exit_shell(argus));
	}
	if (ma_strncmp(argus[0], "alias", 5) == 0)
	{
		ma_alias(argus);
		return (0);
	}
	else if (ma_strncmp(argus[0], "cd", 2) == 0)
	{
		ma_cd(argus[1]);
		return (0);
	}
	else if (ma_strncmp(argus[0], "env", 3) == 0)
		return (ma_env(environ));
	else if (ma_strncmp(argus[0], "setenv", 6) == 0)
	{
		if ((argus[1] == NULL) || (argus[2] == NULL) || (argus[3] != NULL))
		{
			write(2, "usage: setenv VARIABLE VALUE\n", 29);
			return (-1);
		}
		return (ma_setenv(argus[1], argus[2]));
	}
	else if (ma_strncmp(argus[0], "unsetenv", 8) == 0)
	{
		if ((argus[1] == NULL) || (argus[2] != NULL))
		{
			write(2, "usage: unsetenv VARIABLE\n", 25);
			return (-1);
		}
		return (ma_unsetenv(argus[1]));
	}
	return (1);
}
