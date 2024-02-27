#include "main.h"

char *strsep_multi(char **stringp, const char *delim)
{
	if (*stringp == NULL)
	{
		return NULL;
	}

	char *s = strstr(*stringp, delim);
	if (s == NULL)
	{
		char *token = *stringp;
		*stringp = NULL;
		return token;
	}

	*s = '\0';
	char *token = *stringp;
	*stringp = s + strlen(delim);
	return token;
}
