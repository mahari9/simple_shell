#include "shell.h"

/**
 * ma_cd - change the current directory of the process
 * @argv: Array of pointers to the arguments
 *  Return: 0 on success, -1 on failure
 */
int ma_cd(char **argv)
{
	char *cwd = NULL, *home = NULL, *prev_dir = NULL,
	     *dir = argv[1], *old_dir = getcwd(NULL, 0);
	int value;

	track_address(old_dir);
	cwd = getcwd(NULL, 0);
	track_address(cwd);

	if (!argv[1])
	{
		home = ma_getenv("HOME");
		track_address(home);
		if (!home)
			value = chdir((home = ma_getenv("PWD")) ? home : "/");
		else
			value = chdir(home);
	}
	else if (ma_strcmp(dir, "-") == 0)
	{
		prev_dir = ma_getenv("OLDPWD");
		track_address(prev_dir);
		if (!prev_dir)
		{
			write(1, cwd, ma_strlen(cwd));
			write(1, "\n", 1);
			return (1);
		}
		write(1, prev_dir, ma_strlen(prev_dir));
		write(1, "\n", 1);
		value = chdir((prev_dir = ma_getenv("OLDPWD=")) ? prev_dir : "/");
	}
	else
	{
		if (chdir(dir) != 0)
			ma_perror_cd(argv, 3);
		return (-1);
	}
	ma_setenv("OLDPWD", old_dir);
	ma_setenv("PWD", cwd);
	return (value);
}
