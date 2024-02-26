#include "main.h"

/**
 * _get_builtin_fn - Selects the correct function to perform the builtin.
 * @s: Command passed as an argument to the program.
 *
 * Return: Pointer to the function that corresponds to the command,
 *         or NULL if the operator is not one of the expected command.
 */
void (*_get_builtin_fn(char *s))(data_t *data)
{
	int i = 0;

	builtin_t builtins[] = {
		{"env", _builtin_printenv},
		{"setenv", _builtin_set_env},
		{"unsetenv", _builtin_unset_env},
		{"exit", _builtin_exit},
		{NULL, NULL}};

	while (builtins[i].builtin_cmd != NULL)
	{
		if (s != NULL && _strcmp(builtins[i].builtin_cmd, s) == 0)
		{
			return (builtins[i].fn);
		}
		i++;
	}

	return (NULL);
}
