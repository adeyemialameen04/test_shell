#include "main.h"
#include <signal.h>

void sigint_handler(int signo);
void handle_read_and_tok(data_t *data);
void execute_cmd(data_t *data);
void clean(data_t *data);
void shell_loop(data_t *data);
data_t initialize_data_struct(void);

int main(void)
{
	data_t data = initialize_data_struct();
	shell_loop(&data);
	clean(&data);
	return (data.exit_status);
}

data_t initialize_data_struct(void)
{
	data_t data;
	data.prompt = "# ";

	data.cmd = NULL;
	data.argv = NULL;
	data.exit_status = 0;
	data.environ = environ;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("signal");
	}

	return (data);
}

void shell_loop(data_t *data)
{
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			print("$ ", STDOUT_FILENO);
			fflush(stdout);
		}

		handle_read_and_tok(data);

		if (data->argv != NULL && data->argv[0] != NULL)
		{
			execute_cmd(data);
		}

		clean(data);
	}
}

void handle_read_and_tok(data_t *data)
{
	ssize_t read;
	size_t n = 0;

	read = my_getline(&data->cmd, &n, stdin);
	if (read <= 0)
	{
		if (read == 0 || read < 0)
		{
			clean(data);
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(data->exit_status);
		}
	}

	tokenize_command(data);
}

void execute_cmd(data_t *data)
{
	void (*builting_fn)(data_t *data);
	builting_fn = get_builtin_fn(data->argv[0]);

	if (builting_fn != NULL)
	{
		builting_fn(data);
	}
	else
		exec_command(data);
}

void clean(data_t *data)
{
	free_argv(data);

	if (data->cmd != NULL)
	{
		free(data->cmd);
		data->cmd = NULL;
	}

	data->argv = NULL;
}

void sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		print("\n$ ", STDOUT_FILENO);
		fflush(stdout);
	}
}
