#include "main.h"

void count_args(data_t *data, char *token);
void alloc_args(data_t *data);
void copy_args(data_t *data, char *token);

/**
 * _tokenize_command - Function to tokenize the cmd into argv array.
 * @data: The data struct.
 * @delim: Delimeter.
 * Return: 0.
 */
int _tokenize_command(data_t *data, char *delim)
{
	char *cmd_cpy;
	char *token;

	data->cmd[strcspn(data->cmd, "\n")] = '\0';
	cmd_cpy = dup_cmd_str(data->cmd);
	if (cmd_cpy == NULL)
	{
		perror("_strdup failed");
		exit(EXIT_FAILURE);
	}

	token = tokenize_command(cmd_cpy, delim);

	count_args(data, token);
	alloc_args(data);

	free(cmd_cpy);

	cmd_cpy = dup_cmd_str(data->cmd);
	if (cmd_cpy == NULL)
	{
		perror("_strdup failed");
		exit(EXIT_FAILURE);
	}

	token = tokenize_command(cmd_cpy, delim);
	copy_args(data, token);

	free(cmd_cpy);

	return (0);
}

/**
 * dup_cmd_str - Duplicate cmd.
 * @cmd: Cmd to be duplicated.
 * Return: None.
 */
char *dup_cmd_str(char *cmd)
{
	return (_strdup(cmd));
}

/**
 * tokenize_command - Function to tokenize a str.
 * @cmd: The str to be tokenized.
 * @delim: Delimeter.
 * Return: The pointer to the nxt string.
 */
char *tokenize_command(char *cmd, const char *delim)
{
	return (_div_str(cmd, delim));
}

/**
 * count_args - Count the number of arguments(argc).
 * @data: The struct data.
 * @token: Str to be tokenized for counting.
 * Return: None.
 */
void count_args(data_t *data, char *token)
{
	data->argc = 0;

	while (token)
	{
		(data->argc)++;
		token = tokenize_command(NULL, " ");
	}
}

/**
 * alloc_args - Allocate memory for the argv array.
 * @data: The struct data.
 * Return: None.
 */
void alloc_args(data_t *data)
{
	data->argv = malloc((data->argc + 1) * sizeof(char *));

	if (data->argv == NULL)
	{
		perror("malloc failed");
	}
}

/**
 * copy_args - Function to copy the tokens to the argv.
 * @data: The struct data.
 * @token: Token to be copied.
 * Return: None.
 */
void copy_args(data_t *data, char *token)
{
	int i = 0;

	while (token)
	{
		data->argv[i] = _strdup(token);

		if (data->argv[i] == NULL)
		{
			perror("_strdup failed");
			_free_argv(data);
		}

		i++;
		token = tokenize_command(NULL, " ");
	}

	data->argv[i] = NULL;
}
