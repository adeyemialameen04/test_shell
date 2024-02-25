#include "main.h"

void free_argv(data_t *data)
{
	int i;

	if (data->argv != NULL)
	{
		for (i = 0; i < data->argc; i++)
		{
			free(data->argv[i]);
			data->argv[i] = NULL;
		}
		free(data->argv);
		data->argv = NULL;
	}
}
