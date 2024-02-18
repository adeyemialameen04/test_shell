#include <stddef.h>
#include <stdlib.h>

void free_argv(int argc, char ***argv)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		free((*argv)[i]);
		(*argv)[i] = NULL;
	}
	free(*argv);
	*argv = NULL;
}
