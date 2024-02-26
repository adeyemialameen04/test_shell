#include "main.h"

/**
 * _get_path - Function to get the PATH variable from environ.
 * Return: the path or NULL when environ is NULL.
 */
char *_get_path(void)
{
	char **env_ptr;
	char *environ_err = "Error: environ is NULL\n";

	if (environ == NULL)
	{
		_print(environ_err, STDERR_FILENO);
		return (NULL);
	}

	env_ptr = environ;

	while (*env_ptr != NULL)
	{
		if (strncmp(*env_ptr, "PATH=", 5) == 0)
		{
			return (_strdup(*env_ptr + 5));
		}
		env_ptr++;
	}

	return (NULL);
}
