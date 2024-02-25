#include "main.h"

void print(char *printval, int fd)
{
	write(fd, printval, strlen(printval));
}
