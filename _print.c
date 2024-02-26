#include "main.h"

/**
 * _print - Custom write function to print a string or char.
 * @printval: Value to be printed.
 * @fd: File descriptor its printing to.
 * Return: None.
 */
void _print(char *printval, int fd)
{
	write(fd, printval, strlen(printval));
}
