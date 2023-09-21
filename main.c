#include "shell.h"

/**
 * main - the shell program starts exec here
 * @countarg: count-arg
 * @vecarg: vector-arg
 * Return: always success = 0, otherwise err = 1
 */

int main(int countarg, char **vecarg)
{
	information_t info[] = { INFORMATION_INIT };
	int filedisc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filedisc)
		: "r" (filedisc));

	if (countarg == 2)
	{
		filedisc = open(vecarg[1], O_RDONLY);

		if (filedisc == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				_eputcharr(vecarg[0]);
				_eputcharr(": 0: Can't open ");
				_eputcharr(vecarg[1]);
				_putsfinds('\n');
				_putsfinds(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}

		info->readfd = filedisc;
	}

	add_to_env_lst(info);
	rd_hist(info);
	shellhsh(info, vecarg);

	return (EXIT_SUCCESS);
}
