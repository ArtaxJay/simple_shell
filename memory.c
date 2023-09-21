#include "shell.h"

/**
 * freepts - freez pters && NULL's addr
 * @pter: the addr of pterz to be freed
 * Return: 1 if freed, otherwise 0.
 */

int freepts(void **pter)
{
	if (pter && *pter)
	{
		free(*pter);
		*pter = NULL;
		return (1);
	}

	return (0);
}
