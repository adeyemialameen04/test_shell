#include "main.h"
#include <signal.h>

void sigint_handler(int signo);

int main(void)
{
	data_t data;
	ssize_t read;
	size_t n = 0;
	char *prompt = "# ";

	data.cmd = NULL;
	data.argv = NULL;
	data.exit_status = 0;

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

		read = my_getline(&data.cmd, &n, stdin);
		if (read <= 0)
		{
			if (read == 0)
			{
				break;
			}
			else
			{
				printf("\n");
				break;
			}
		}

		tokenize_command(&data);

		if (data.argv != NULL && data.argv[0] != NULL)
		{

			if (strcmp(data.argv[0], "env") == 0)
			{
				printenv();
			}
			else
			{
				exec_command(&data, &data.exit_status);
			}
		}

		free_argv(&data);
		free(data.cmd);
		data.cmd = NULL;
		data.argv = NULL;
	}

	free_argv(&data);
	free(data.cmd);
	return (data.exit_status);
}

void sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n$ ", 3);
	}
}
