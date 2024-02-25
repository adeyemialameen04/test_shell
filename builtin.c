#include "main.h"

void builtin_set_env(data_t *data)
{
	if (data->argv[1] == NULL || data->argv[2] == NULL ||
		*data->argv[1] == '\0' ||
		*data->argv[2] == '\0')
	{
		print("setenv: Invalid arguments\n", STDERR_FILENO);
		return;
	}

	if (setenv(data->argv[1], data->argv[2], 1) != 0)
	{
		print("setenv", STDERR_FILENO);
	}

	data->environ = environ;
}

void builtin_unset_env(data_t *data)
{
	if (data->argv[1] == NULL || *data->argv[1] == '\0')
	{
		print("unsetenv: Invalid arguments\n", STDERR_FILENO);
		return;
	}

	if (unsetenv(data->argv[1]) != 0)
	{
		print("unsetenv", STDERR_FILENO);
	}

	data->environ = environ;
}

void printenv(data_t *data)
{
	unsigned int i = 0;

	while (data->environ[i])
	{
		print(data->environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
		i++;
	}
}

void builtin_exit(data_t *data)
{
	if (data->argv[1] != NULL)
	{
		if (data->argv[1][0] == '-' || !is_num(data->argv[1]))
		{
			print_exit_err(data);
			data->exit_status = 2;
		}
		else
		{
			data->exit_status = atoi(data->argv[1]);

			free_argv(data);
			free(data->cmd);
			exit(data->exit_status);
		}
	}
	else
	{
		free_argv(data);
		free(data->cmd);
		exit(data->exit_status);
	}
}
