#include "main.h"

void print_not_found(data_t *data)
{
	char *err_msg = "./hsh: 1: ";
	char *not_found = ": not found\n";

	print(err_msg, STDERR_FILENO);
	print(data->argv[0], STDERR_FILENO);
	print(not_found, STDERR_FILENO);
}

void print_exit_err(data_t *data)
{
	char *err_msg = "./hsh: 1: ";
	char *illegal_num = "exit: Illegal number: ";

	print(err_msg, STDERR_FILENO);
	print(illegal_num, STDERR_FILENO);
	print(data->argv[1], STDERR_FILENO);
	print("\n", STDERR_FILENO);
}
