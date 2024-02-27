#include "main.h"

/**
 * _free_argv - Free the elements inside argv and set to NULL.
 * @data: The data struct.
 * Return: none.
 */
void _free_argv(data_t *data)
{
	int i;

	if (data->argv != NULL)
	{
		for (i = 0; data->argv[i] != NULL; i++)
		{
			free(data->argv[i]);
			data->argv[i] = NULL;
		}
		free(data->argv);
		data->argv = NULL;
	}
}

/**
 * _clean - Function to free the data struct memory.
 * @data: The data struct.
 * Return: None.
 */
void _clean(data_t *data)
{
	_free_argv(data);
	_free_cmd(data);
	_free_cmds(data);
}

void _free_cmd(data_t *data)
{
	if (data->cmd != NULL)
	{
		free(data->cmd);
		data->cmd = NULL;
	}
}

/**
 * _free_cmds - Free the elements inside argv and set to NULL.
 * @data: The data struct.
 * Return: none.
 */
void _free_cmds(data_t *data)
{
	int i;

	if (data->cmds == NULL)
		return;

	for (i = 0; i < data->cmds_count; i++)
	{
		free(data->cmds[i].command);
		free(data->cmds[i].operator);
	}
	free(data->cmds);
	data->cmds = NULL;
}
