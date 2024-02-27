#include "main.h"

void count_cmds(data_t *data, char *token);
void alloc_cmds(data_t *data);
void copy_cmds(data_t *data, char *token, char *nxt_operator);

/**
 * _split_command - Function to tokenize the cmd into argv array.
 * @data: The data struct.
 * @delim: Delimiter.
 * Return: None.
 */
void _split_command(data_t *data)
{
	char *cmd_cpy, *cmd_coppy;
	char *token, *nxt_operator;

	/*Ensure cmd is null-terminated*/
	data->cmd[strcspn(data->cmd, "\n")] = '\0';

	/*Duplicate the command string*/
	cmd_cpy = dup_cmd_str(data->cmd);
	if (cmd_cpy == NULL)
	{
		perror("_strdup failed");
		exit(EXIT_FAILURE);
	}

	token = strtok_r(cmd_cpy, ";&&||", &nxt_operator);

	count_cmds(data, token);
	alloc_cmds(data);
	free(cmd_cpy);

	cmd_coppy = dup_cmd_str(data->cmd);
	if (cmd_coppy == NULL)
	{
		perror("_strdup failed");
		exit(EXIT_FAILURE);
	}

	token = strtok_r(cmd_coppy, ";&&||", &nxt_operator);
	copy_cmds(data, token, nxt_operator);

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
	data->cmds = malloc((data->cmds_count + 1) * sizeof(command_t));
	if (data->cmds == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
}

void copy_cmds(data_t *data, char *token, char *nxt_operator)
{
	int i = 0;

	/*Copy the commands into the allocated memory*/
	while (token != NULL)
	{
		data->cmds[i].command = strdup(token);
		data->cmds[i].operator= nxt_operator ? strdup(nxt_operator) : NULL;
		if (data->cmds[i].command == NULL)
		{
			perror("_strdup failed");
			_free_cmds(data);
			exit(EXIT_FAILURE);
		}
		i++;
		token = strtok_r(NULL, ";&&||", &nxt_operator);
	}

	data->cmds[i].command = NULL;
	data->cmds[i].operator= NULL;
}
