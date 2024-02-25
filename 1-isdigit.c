#include "main.h"

/**
 * _isdigit - Checks if a character is a digit.
 *
 * @c: The character to be checked.
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int is_num(char *str)
{
	while (*str != '\0')
	{
		if (!_isdigit(*str))
		{
			return (0);
		}
		str++;
	}
	return (1);
}
