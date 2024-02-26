#include "main.h"

char *_find_command(char *cmd, char *ph);
/**
 * _find_command - This function checks for the command in the PATH varible and
 *					checks if its an executable
 * @cmd: command to be checked for
 * @ph: PATH
 * Return: NULL is the command is not found, full_path is the
 *			command is found and executable
 */
char *_find_command(char *cmd, char *ph)
{
	char *ph_cpy;
	char *ph_dir;
	char *saveptr;
	size_t full_ph_len;
	char *full_ph;

	if (ph == NULL)
		return (NULL);

	ph_cpy = _strdup(ph);
	if (ph_cpy == NULL)
	{
		perror("_strdup failed");
	}

	ph_dir = strtok_r(ph_cpy, ":", &saveptr);
	while (ph_dir)
	{
		full_ph_len = strlen(ph_dir) + strlen(cmd) + 2;
		full_ph = malloc(full_ph_len);
		if (full_ph == NULL)
		{
			perror("malloc");
			free(ph_cpy);
			return (NULL);
		}

		snprintf(full_ph, full_ph_len, "%s/%s", ph_dir, cmd);

		if (access(full_ph, X_OK) == 0)
		{
			free(ph_cpy);
			return (full_ph);
		}

		free(full_ph);

		ph_dir = strtok_r(NULL, ":", &saveptr);
	}

	free(ph_cpy);
	return (NULL);
}
