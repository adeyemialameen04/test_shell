#include "main.h"

#define INITIAL_BUFFER_SIZE 1024

char *allocate_buffer(char *buffer, size_t *bufsize)
{
	buffer = malloc(INITIAL_BUFFER_SIZE);
	if (buffer == NULL)
	{
		return NULL;
	}
	*bufsize = INITIAL_BUFFER_SIZE;
	return buffer;
}

char *reallocate_buffer(char *buffer, size_t *bufsize)
{
	*bufsize *= 2;
	buffer = realloc(buffer, *bufsize);
	return buffer;
}

ssize_t read_from_stream(int fd, char *buffer, size_t position)
{
	ssize_t bytes_read = read(fd, &buffer[position], 1);
	return bytes_read;
}

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer = *lineptr;
	size_t bufsize = *n;
	size_t position = 0;
	int fd = fileno(stream);
	ssize_t bytes_read;

	if (buffer == NULL)
	{
		buffer = allocate_buffer(buffer, &bufsize);
		if (buffer == NULL)
		{
			return -1;
		}
	}

	while (1)
	{
		if (position >= bufsize)
		{
			buffer = reallocate_buffer(buffer, &bufsize);
			if (buffer == NULL)
			{
				return -1;
			}
		}

		bytes_read = read_from_stream(fd, buffer, position);
		if (bytes_read <= 0)
		{
			if (bytes_read == -1)
			{
				perror("read");
			}
			break;
		}

		if (buffer[position] == '\n')
		{
			position++;
			break;
		}

		position++;
	}

	buffer[position] = '\0';
	position--;
	*lineptr = buffer;
	*n = bufsize;

	if (*lineptr != buffer)
	{
		free(buffer);
	}

	return (position);
}
