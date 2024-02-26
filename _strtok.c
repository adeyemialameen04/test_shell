#include "main.h"

/**
 * _div_str - A custom strtok function
 * @str: The string to be tokenized.
 * @delim: Delimeter.
 * Return: The pointer to the next string if a token is found.
 */
char *_div_str(char *str, const char *delim)
{
	static char *buffer;
	char *token_start;

	if (str != NULL)
		buffer = str;
	if (buffer == NULL)
		return (NULL);

	token_start = buffer;
	while (*buffer != '\0')
	{
		const char *d = delim;

		while (*d)
		{
			if (*buffer == *d++)
			{
				*buffer = '\0';
				buffer++;
				while (*buffer == ' ' && *buffer != '\0')
					buffer++;
				if (*token_start == '\0')
				{
					token_start = buffer;
					continue;
				}
				return (token_start);
			}
		}
		if (*buffer == '\0')
			break;
		buffer++;
	}
	return ((*token_start == '\0') ? NULL : token_start);
}
