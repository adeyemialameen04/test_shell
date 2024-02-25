#include "main.h"

void (*get_builtin_fn(char *s))(data_t *data)
{
	int i = 0;

	builtin_t builtins[] = {
		{"env", printenv},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{"exit", builtin_exit},
		{NULL, NULL}};

	while (builtins[i].builtin_cmd != NULL)
	{
		if (strcmp(builtins[i].builtin_cmd, s) == 0)
		{
			return (builtins[i].fn);
		}
		i++;
	}

	return (NULL);
}
