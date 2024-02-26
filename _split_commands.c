#include "main.h"

void count_cmds(data_t *data, char *token);
void alloc_cmds(data_t *data);
void copy_cmds(data_t *data, char *token);

/**
 * _split_command - Function to tokenize the cmd into argv array.
 * @data: The data struct.
 * @delim: Delimiter.
 * Return: None.
 */
void _split_command(data_t *data, char *delim)
{
	char *cmd_cpy, *cmd_coppy;
	char *token;

	/*Ensure cmd is null-terminated*/
	data->cmd[strcspn(data->cmd, "\n")] = '\0';

	/*Duplicate the command string*/
	cmd_cpy = dup_cmd_str(data->cmd);
	if (cmd_cpy == NULL)
	{
		perror("_strdup failed");
		exit(EXIT_FAILURE);
	}

	token = tokenize_command(cmd_cpy, delim);

	count_cmds(data, token);
	alloc_cmds(data);
	free(cmd_cpy);

	cmd_coppy = dup_cmd_str(data->cmd);
	if (cmd_coppy == NULL)
	{
		perror("_strdup failed");
		exit(EXIT_FAILURE);
	}

	token = tokenize_command(cmd_coppy, delim);
	copy_cmds(data, token);

	free(cmd_coppy);
}

void count_cmds(data_t *data, char *token)
{
	data->cmds_count = 0;

	while (token)
	{
		data->cmds_count++;
		token = tokenize_command(NULL, ";");
	}
}

void alloc_cmds(data_t *data)
{

	/*Allocate memory for the commands array*/
	data->cmds = malloc((data->cmds_count + 1) * sizeof(char *));
	if (data->cmds == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
}

void copy_cmds(data_t *data, char *token)
{
	int i = 0;

	/*Copy the commands into the allocated memory*/
	while (token != NULL)
	{
		data->cmds[i] = strdup(token);
		if (data->cmds[i] == NULL)
		{
			perror("_strdup failed");
			_free_cmds(data);
			exit(EXIT_FAILURE);
		}
		i++;
		token = tokenize_command(NULL, ";");
	}

	data->cmds[i] = NULL;
}
