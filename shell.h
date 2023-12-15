#ifndef SHELL_H
#define SHELL_H

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
#define MAXALS 25

#define WRT(e) (write(STDERR_FILENO, e, ma_strlen(e)))

/**
 * struct pair_entry - Pair entry Used for
 * implementation env built-in and alias
 * @name: name or key part of enviromental variables
 * @value: value part of environmental variables
 */
typedef struct pair_entry
{
	char *name;
	char *value;
} pair_entry;

/**
 * struct alias_list - Pair entr Used for implementation built-in alias
 * @aliases: the each number of aliases
 * @a_count: alias counter
 */
typedef struct alias_list
{
	pair_entry aliases[MAXALS];
	int a_count;
} alias_list;

/********* global variable declaration****/
alias_list G_alias;
char *usrin, char *shell;
int count, num_p, status, source, replflag;
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
void append_str(char **buffer, char *str, int n, size_t *i);
char *ma_strchr(const char *s, int crt);

/******* builti-in  *****************/
char **impl_env(char **ma_environ);
int ma_env(char **envm);
int ma_cd(char **argus);
void exit_shell(char **argus);
char *create_env(char *name, char *value);
int ma_setenv(char *name, char *value);
int ma_unsetenv(char *name);
int track_address(void *p);
char *search_alias(char *name, int *row);
void define_alias(char *al_name, char *al_value);
void print_alias(int r);
void ma_alias(char **argus);

/**********memory mang *********/
void *ma_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *ma_memcpy(char *dst, char *src, unsigned int n);
void initialize_alias_count(void);
void deallocate_env(void);
void deallocate(char **argus, char *usrin);

/********error handler and printers******/
char *display_error(char **argus);
char *display_error126(char **argus);
void display_errorexit(char **argus);
void ma_perror_cd(char **argus, int cod);
int ma_perror(char **argus, int cod);
void ma_perrorfile(char **argv);
char *ma_cd_error(char **argus);
char *ma_cd_error1(char **argus);

/********  getline and process ******/
ssize_t ma_getline(char **linept, size_t *n, int fd);
int ma_getc(int fd);
void fill_buffer(int fd, char *buffer, size_t *index, size_t *rd);
char *hashtag_comm(char *line);
char *ma_process_line(char *line);
int get_process_stdininput(void);
int validate_file(const char *pn);
void ma_readprocess_execute_file(const char *filename, char **argv);
int ma_parser(char *usri);
int handle_opera(char *cmd, char *opr);
int ma_separat(char *usri);
char *ma_strtok(char *usrin, const char *separ);
int main(int argc, char **argv);

/******* execution commands *******/
int handle_commands(char **argus);
int execute_builtin(char **argus);
int inputcommand_execute(char **argv, char **envm);
int p_process(char **argus, pid_t pid);

/******* variable rplace handler********/
char *impl_var(char *cmd);
char *update_var(char *cmd);

/*******signal catcher and prompt ******/
void signal_catcher(int sign_num);
int setup_signal_catcher(void);
void display_prompt(void);
void print_o(const char *message);

/********ma_whichpath **********/
char *ma_whichpath(char *cmnd);
char *ma_buildpath(char *comp, char *dir);
char *ma_getenv(const char *name);

#endif
