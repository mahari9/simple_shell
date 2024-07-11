#include "shell.h"

/**
 * display_prompt - Function that displays the prompt
 *
 * Return: Nothing
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
