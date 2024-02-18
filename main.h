#ifndef _MAIN_H_
#define _MAIN_H_

void tokenize_command(char *cmd, int *argc, char ***argv);
void free_dup(char *str);
int exec_command(char **argv);
char *_strdup(char *str);
void free_argv(int argc, char ***argv);

#endif /* #ifndef _MAIN_H_ */
