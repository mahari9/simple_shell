#include "shel.h"

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
		exit_shell(argus);
		return (0);
	}
	else if (ma_strncmp(argus[0], "env", 3) == 0)
		return (ma_env(environ));

	return (1);
}
