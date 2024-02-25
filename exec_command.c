#include "main.h"

char *get_cmd_path(data_t *data, char *path);
int start_child_process(data_t *data, char *cmd_ph);
int wait_for_child_process(__pid_t pid, data_t *data, char *cmd_ph);

int exec_command(data_t *data)
{
	__pid_t pid;
	char *path = get_path();
	char *cmd_ph = get_cmd_path(data, path);

	free(path);

	if (cmd_ph == NULL)
	{
		print_not_found(data);
		data->exit_status = 127;
		return (data->exit_status);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(cmd_ph);
		return (-1);
	}
	else if (pid == 0)
	{
		int result = start_child_process(data, cmd_ph);
		free(cmd_ph);
		return (result);
	}
	else
	{
		int result = wait_for_child_process(pid, data, cmd_ph);
		free(cmd_ph);
		return (result);
	}

	free(cmd_ph);
	return (0);
}

char *get_cmd_path(data_t *data, char *path)
{
	char *cmd_ph;

	if (
		data->argv[0][0] == '/' ||
		strncmp(data->argv[0], "./", 2) == 0 ||
		strncmp(data->argv[0], "../", 3) == 0 ||
		strncmp(data->argv[0], "../../", 6) == 0)
	{
		cmd_ph = strdup(data->argv[0]);
	}
	else
		cmd_ph = find_command(data->argv[0], path);

	return (cmd_ph);
}

int start_child_process(data_t *data, char *cmd_ph)
{
	int res = execve(cmd_ph, data->argv, NULL);

	if (res == -1)
	{
		free_argv(data);
		free(data->cmd);
		free(cmd_ph);
		exit(127);
	}

	return (0);
}

int wait_for_child_process(__pid_t pid, data_t *data, char *cmd_ph)
{
	int status;

	while (1)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			if (errno != EINTR)
				continue;
			perror("waitpid");
			free(cmd_ph);
			return (-1);
		}
		break;
	}

	if (WIFEXITED(status))
	{
		data->exit_status = WEXITSTATUS(status);
	}

	return (0);
}
