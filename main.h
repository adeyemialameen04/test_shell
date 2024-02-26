#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <ctype.h>

extern char **environ;

/*STRUCTS*/
typedef struct data
{
	int argc;
	char **argv;
	char *cmd;
	char **cmds;
	int cmds_count;
	int exit_status;
	char **environ;
	int cmds_alloc;
	char *prompt;
} data_t;

typedef struct builtin_struct
{
	char *builtin_cmd;
	void (*fn)(data_t *data);
} builtin_t;

int _shell(void);

/*SHELL HELPER FUNCTIONS*/
void sigint_handler(int signo);
void handle_read_and_tok(data_t *data);
void execute_cmd(data_t *data);
void _clean(data_t *data);
void shell_loop(data_t *data);
data_t initialize_data_struct(void);

/*CORE FUNCTIONS*/
char *tokenize_command(char *cmd, const char *delim);
char *dup_cmd_str(char *cmd);
int _tokenize_command(data_t *data, char *delim);
int _exec_command(data_t *data);

void _free_cmd(data_t *data);
void _free_argv(data_t *data);
void _free_cmds(data_t *data);

void _split_command(data_t *data, char *delim);

/*INT HELPER FUNCTIONS*/
int _isdigit(int c);
int _is_num(char *str);

/*PRINT*/
void _print(char *printval, int fd);

/*PRINT ERRS*/
void _print_not_found(data_t *data);
void _print_exit_err(data_t *data);

/*CUSTOM FUNCTIONS*/
ssize_t _read_line(char **lineptr, size_t *n, FILE *stream); /*getline*/
char *_div_str(char *str, const char *delim);				 /*strtok*/

/*PATH*/
char *_get_path();
char *_find_command(char *cmd, char *ph);

/*BUILTINS*/
void (*_get_builtin_fn(char *s))(data_t *data);
void _builtin_printenv(data_t *data);
void _builtin_exit(data_t *data);
void _builtin_set_env(data_t *data);
void _builtin_unset_env(data_t *data);

/*STRING FUNCTIONS*/
int _atoi(char *s);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strdup(char *str);
char *_strchr(char *s, char c);

#endif /* #ifndef _MAIN_H_ */
