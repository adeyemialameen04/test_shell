#include "main.h"
#include <signal.h>

void sigint_handler(int signo);
void handle_read_and_tok(data_t *data);
void execute_cmd(data_t *data);
void clean(data_t *data);

int main(void)
{
	data_t data;
	char *prompt = "# ";

	data.cmd = NULL;
	data.argv = NULL;
	data.exit_status = 0;
	data.environ = environ;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("signal");
		return (EXIT_FAILURE);
	}

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("%s", prompt);
			fflush(stdout);
		}

		handle_read_and_tok(&data);

		if (data.argv != NULL && data.argv[0] != NULL)
		{
			execute_cmd(&data);
		}

		clean(&data);
	}

	free_argv(&data);
	free(data.cmd);
	free(data.cmd);
	return (data.exit_status);
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
	free(data->cmd);
	data->cmd = NULL;
	data->argv = NULL;
}

void sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		print("\n$ ", STDOUT_FILENO);
	}
}
