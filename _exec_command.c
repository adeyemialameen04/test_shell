#include "main.h"

static char *_get_cmd_path(data_t *data, char *path);
static int _start_child_process(data_t *data, char *cmd_ph);
static int _wait_for_child_process(__pid_t pid, data_t *data, char *cmd_ph);

/**
 * _exec_command - Execute an external command
 *
 * @data: Pointer to the data structure containing command information
 *
 * This function is responsible for executing an external command specified
 * in the data structure. It handles forking a child process, executing the
 * command, and waiting for the child process to complete.
 *
 * Return: Returns the exit status of the executed command or -1 in case
 *			of an error.
 */
int _exec_command(data_t *data)
{
	__pid_t pid;
	char *path = _get_path();
	char *cmd_ph = _get_cmd_path(data, path);

	free(path);

	if (cmd_ph == NULL)
	{
		_print_not_found(data);
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
		int result = _start_child_process(data, cmd_ph);

		free(cmd_ph);
		return (result);
	}
	else
	{
		int result = _wait_for_child_process(pid, data, cmd_ph);

		free(cmd_ph);
		return (result);
	}

	free(cmd_ph);
	return (0);
}

/**
 * _get_cmd_path - This function returns the cmd_ph
 * @data: data struct
 * @path: The path variable from the envs.
 * Return: The command found
 */
static char *_get_cmd_path(data_t *data, char *path)
{
	char *cmd_ph;

	if (
		data->argv[0][0] == '/' ||
		strncmp(data->argv[0], "./", 2) == 0 ||
		strncmp(data->argv[0], "../", 3) == 0 ||
		strncmp(data->argv[0], "../../", 6) == 0)
	{
		cmd_ph = _strdup(data->argv[0]);
	}
	else
		cmd_ph = _find_command(data->argv[0], path);

	return (cmd_ph);
}

/**
 * _start_child_process - Starts the child process
 * @data: Struct data.
 * @cmd_ph: The command path.
 * Return: 0 on success
 */
static int _start_child_process(data_t *data, char *cmd_ph)
{
	int res = execve(cmd_ph, data->argv, NULL);

	if (res == -1)
	{
		_free_argv(data);
		_free_cmds(data);
		free(data->cmd);
		free(cmd_ph);
		exit(127);
	}

	return (0);
}

/**
 * _wait_for_child_process - This function waits for the child process to
 *								finish executing.
 * @pid: The pid of the child process.
 * @data: The data struct
 * @cmd_ph: The command path.
 * Return: -1 if an error occured and 0for otherwise.
 */
static int _wait_for_child_process(__pid_t pid, data_t *data, char *cmd_ph)
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
