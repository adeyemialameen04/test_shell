#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

typedef struct data
{
	int argc;
	char **argv;
	char *cmd;
	int exit_status;
	char **environ;
	char *prompt;
} data_t;

typedef struct builtin_struct
{
	char *builtin_cmd;
	void (*fn)(data_t *data);
} builtin_t;

int tokenize_command(data_t *data);
int exec_command(data_t *data);
void free_argv(data_t *data);
void printenv(data_t *data);
char *_strdup(char *str);
int _printf(const char *format, ...);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
int _isdigit(int c);
int is_num(char *str);
void print(char *printval, int fd);
void print_not_found(data_t *data);
void print_exit_err(data_t *data);
char *div_str(char *str, const char *delim);
void (*get_builtin_fn(char *s))(data_t *data);
void builtin_exit(data_t *data);
char *get_path();
char *find_command(char *cmd, char *ph);
void builtin_set_env(data_t *data);
void builtin_unset_env(data_t *data);
int _putchar(char c);

#endif /* #ifndef _MAIN_H_ */
