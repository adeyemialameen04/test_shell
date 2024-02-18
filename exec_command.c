#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int exec_command(char **argv)
{
	__pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (argv[0] != NULL)
		{
			execvp(argv[0], argv);
		}
		else
		{
			fprintf(stderr, "argv[0] is NULL\n");
			exit(EXIT_FAILURE);
		}

		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		while (1)
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				if (errno != EINTR)
					continue;
				perror("waitpid");
				return (-1);
			}
			break;
		}
	}

	return (0);
}
