#include "main.h"

char *get_path(void)
{
	char **env_ptr;
	char *environ_err = "Error: environ is NULL\n";

	if (environ == NULL)
	{
		print(environ_err, STDERR_FILENO);
		return (NULL);
	}

	env_ptr = environ;

	while (*env_ptr != NULL)
	{
		if (strncmp(*env_ptr, "PATH=", 5) == 0)
		{
			return (strdup(*env_ptr + 5));
		}
		env_ptr++;
	}

	return (NULL);
}
