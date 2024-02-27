#include "main.h"

/**
 * initialize_data_struct - Initialize data struct.
 * Return: the data_t struct.
 */
data_t initialize_data_struct(void)
{
	data_t data;

	data.prompt = "$ ";
	data.cmd = NULL;
	data.argv = NULL;
	data.cmds = NULL;
	data.exit_status = 0;
	data.environ = environ;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("signal");
	}

	return (data);
}

/**
 * shell_loop - Shell loop to keeping running the shell program.
 * @data: The data struct.
 * Return: None.
 */
void shell_loop(data_t *data)
{
	int i;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			_print("$ ", STDOUT_FILENO);
			fflush(stdout);
		}

		handle_read_and_tok(data);

		for (i = 0; i < data->cmds_count; i++)
		{
			if (i == 0 || (strcmp(data->cmds[i - 1].operator, "&&") == 0 && status == 0) || (strcmp(data->cmds[i - 1].operator, "||") == 0 && status != 0))
			{
				data->cmd = data->cmds[i].command;
				_tokenize_command(data, " \n");
				status = execute_cmd(data);
			}
			_free_argv(data);
		}
		_free_cmds(data);
	}
}

/**
 * handle_read_and_tok - Function to handle reading and
 *							tokenizing the command.
 * @data: The data struct.
 * Return: None.
 */
void handle_read_and_tok(data_t *data)
{
	ssize_t read;
	size_t n = 0;

	_free_argv(data);
	_free_cmds(data);

	read = getline(&data->cmd, &n, stdin);
	if (read == 0 || read < 0)
	{
		free(data->cmd);
		data->cmd = NULL;
		_free_argv(data);
		_free_cmds(data);
		if (isatty(STDIN_FILENO))
			_print("\n", STDOUT_FILENO);
		exit(data->exit_status);
	}

	_split_command(data);
	free(data->cmd);
	data->cmd = NULL;
}

/**
 * execute_cmd - Function to determine if cmd is a builtin or not
 *					execute the builtin if it is a builtin
 *						or the _exec_command if not.
 * @data: The data struct.
 * Return: None.
 */
int execute_cmd(data_t *data)
{
	void (*builting_fn)(data_t *data);

	if (data->argv[0] == NULL)
		return 0;

	builting_fn = _get_builtin_fn(data->argv[0]);

	if (builting_fn != NULL)
	{
		builting_fn(data);
		return data->exit_status;
	}
	else
		return _exec_command(data);
}
