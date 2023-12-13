#include "shell.h"

/**
 * display_prompt - Function that displays the prompt
 *
 * Return: Nothing
 */
void display_prompt(void)
{
	print_o("$ ");
}

/**
 * print_o - costum printer fuction
 * @message: Text to be printed
 * Return: Nothing
 */
void print_o(const char *message)
{
	write(STDOUT_FILENO, message, ma_strlen(message));
}
