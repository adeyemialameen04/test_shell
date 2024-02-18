#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void tokenize_command(char *cmd, int *argc, char ***argv)
{
	char *cmd_copy;
	char *delim = " \n";
	char *token;
	int i = 0;
	int j;

	cmd[strcspn(cmd, "\n")] = '\0';

	cmd_copy = strdup(cmd);
	if (cmd_copy == NULL)
	{
		perror("strdup failed");
		exit(EXIT_FAILURE);
	}

	token = strtok(cmd_copy, delim);
	*argc = 0;

	while (token)
	{
		(*argc)++;
		token = strtok(NULL, delim);
	}

	*argv = malloc(((*argc) + 1) * sizeof(char *));
	if (*argv == NULL)
	{
		perror("malloc failed");
		free(cmd_copy);
		exit(EXIT_FAILURE);
	}

	token = strtok(cmd, delim);
	i = 0;

	while (token)
	{
		(*argv)[i] = strdup(token);
		if ((*argv)[i] == NULL)
		{
			perror("strdup failed");

			for (j = 0; j < i; j++)
			{
				free((*argv)[j]);
			}
			free(*argv);
			free(cmd_copy);
			exit(EXIT_FAILURE);
		}
		i++;
		token = strtok(NULL, delim);
	}

	(*argv)[i] = NULL;
	if ((*argv)[0] == NULL)
	{
		free_argv(*argc, argv);
		free(*argv);
	}

	free(cmd_copy);
}
