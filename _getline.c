#include "main.h"

#define INITIAL_BUFFER_SIZE 1024

/**
 * alloc_buf - Allocate memory for the buffer.
 * @buffer: Buffer.
 * @bufsize: The buf size.
 * Return: The buffer.
 */
char *alloc_buf(char *buffer, size_t *bufsize)
{
	buffer = malloc(INITIAL_BUFFER_SIZE);
	if (buffer == NULL)
	{
		return (NULL);
	}
	*bufsize = INITIAL_BUFFER_SIZE;
	return (buffer);
}

/**
 * realloc_buf - Reallocate memory for the buffer when buf_size
 *					has ran out.
 * @buffer: Buffer.
 * @bufsize: The buf size.
 * Return: The buffer.
 */
char *realloc_buf(char *buffer, size_t *bufsize)
{
	*bufsize *= 2;
	buffer = realloc(buffer, *bufsize);
	return (buffer);
}

/**
 * read_from_stream - Read characters from stream.
 * @fd: File descriptor.
 * @buffer: The buffer its being read to.
 * @position:Position of where the buffer is.
 * Return: The number of bytes read.
 */
ssize_t read_from_stream(int fd, char *buffer, size_t position)
{
	ssize_t bytes_read = read(fd, &buffer[position], 1);

	return (bytes_read);
}

ssize_t _read_line(char **lineptr, size_t *n, FILE *stream);
/**
 * _read_line - Custom getline function.
 * @lineptr: stores the adress of the buffer.
 * @n: size.
 * @stream: Where its reading from.
 * Return: Number of chars read on sucess.
 */
ssize_t _read_line(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer = *lineptr;
	size_t bufsize = *n;
	size_t position = 0;
	int fd = fileno(stream);
	ssize_t bytes_read;

	if (buffer == NULL)
	{
		buffer = alloc_buf(buffer, &bufsize);
		if (buffer == NULL)
		{
			return (-1);
		}
	}

	while (1)
	{
		if (position >= bufsize)
		{
			buffer = realloc_buf(buffer, &bufsize);
			if (buffer == NULL)
			{
				return (-1);
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
