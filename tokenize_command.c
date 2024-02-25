#include "main.h"

int tokenize_command(data_t *data)
{
	char *cmd_cpy;
	char *delim = " \n";
	char *token;
	int i = 0;

	data->cmd[strcspn(data->cmd, "\n")] = '\0';
	cmd_cpy = strdup(data->cmd);
	token = div_str(cmd_cpy, delim);

	if (cmd_cpy == NULL)
	{
		perror("strdup failed");
		exit(EXIT_FAILURE);
	}

	data->argc = 0;

	while (token)
	{
		(data->argc)++;
		token = div_str(NULL, delim);
	}

	free(cmd_cpy);

	data->argv = malloc(((data->argc) + 1) * sizeof(char *));
	if (data->argv == NULL)
	{
		perror("malloc failed");
		return (-1);
	}

	token = div_str(data->cmd, delim);

	while (token)
	{
		data->argv[i] = strdup(token);
		if (data->argv[i] == NULL)
		{
			perror("strdup failed");
			free_argv(data);
			return (-1);
		}
		i++;
		token = div_str(NULL, delim);
	}

	data->argv[i] = NULL;

	return (0);
}
