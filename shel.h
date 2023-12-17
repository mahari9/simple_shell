#ifndef SHEL_H
#define SHEL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stddef.h>


extern char **environ;

/**MACROS**/
#define BUFFMAXSIZE 1024

#define WRT(e) (write(STDERR_FILENO, e, ma_strlen(e)))

/**
 * struct pair_entry - Pair entry Used for
 * implementation env built-in
 * @name: name or key part of enviromental variables
 * @value: value part of environmental variables
 */
typedef struct pair_entry
{
	char *name;
	char *value;
} pair_entry;

char *usrin, *shell;
int count, status, source, no_pth;
void *env_n[50];

/*********** string_manp.c *******/
int ma_strlen(const char *str);
char *ma_strcpy(char *dst, char *src);
char *ma_strdup(const char *str);
char *ma_strndup(const char *str, size_t n);
char *ma_strcat(char *dst, const char *src);

/************** string_manp1.c ********/
int ma_strcmp(char *str1, char *str2);
int ma_strncmp(const char *str1, const char *str2, size_t n);
int ma_isalpha(char c);
int ma_atoi(char *str);
char *ma_strstr(char *hystk, char *ndl);

/******** string_manp2.c *********/
char *ma_itoa(int num);
int count_digits(int num);
int ma_puts(char *cos);
char *ma_strchr(const char *s, int crt);

/******* builti-in  *****************/
char **impl_env(char **ma_environ);
int ma_env(char **envm);
void exit_shell(char **argv);

/**********memory mang *********/
void deallocate(char **argus);
void sweep_all(char **argus);

/********error handler and printers******/
char *display_error(char **argus);
char *display_error126(char **argus);
void display_errorexit(char **argus);
int ma_perror(char **argus, int cod);

/********  getline and process ******/
char **ma_parser(char *usri);
char **separator(char *usri);
int main(int argc, char **argv);

/******* execution commands *******/
int inputcommand_execute(char **argv, char **envm);
int p_process(char **argus, pid_t pid);

/*******signal catcher and prompt ******/
void display_prompt(void);
void print_o(const char *message);

/********ma_whichpath **********/
char *ma_whichpath(char *cmnd);
char *ma_buildpath(char *comp, char *dir);
char *ma_getenv(const char *name);

#endif
