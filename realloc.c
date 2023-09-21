#include "shell.h"

/**
 **_memconstbyte - populates mem wth const bytes
 *@memalloc: d pter to d mem allocated
 *@popubyte: d byte to occupy *ptr memalloc with
 *@byteamnt: the amnt of bytes to be populated
 *Return: memalloc -- a pter to d memory area
 */

char *_memconstbyte(char *memalloc, char popubyte, unsigned int byteamnt)
{
	unsigned int iterator;

	iterator = 0;
	while (iterator < byteamnt)
	{
		memalloc[iterator] = popubyte;
		iterator++;
	}

	return (memalloc);
}

/**
 * disectfree - frez strng of strngs
 * @strostrs: str of strs
 */

void disectfree(char **strostrs)
{
	char **a = strostrs;

	if (!strostrs)
		return;

	while (*strostrs)
		free(*strostrs++);

	free(a);
}

/**
 * _my_realloc - reallocs blocks of mem
 * @pter: pter 2 prev malloc
 * @siz_prev: byte size of prev blck
 * @siz_new: byte size of new blck
 * Return: pter to dblok
 */

void *_my_realloc(void *pter, unsigned int siz_prev, unsigned int siz_new)
{
	char *ptersvar;

	if (!pter)
		return (malloc(siz_new));

	if (!siz_new)
		return (free(pter), NULL);

	if (siz_new == siz_prev)
		return (pter);

	ptersvar = malloc(siz_new);

	if (!ptersvar)
		return (NULL);

	siz_prev = siz_prev < siz_new ? siz_prev : siz_new;

	while (siz_prev--)
		ptersvar[siz_prev] = ((char *)pter)[siz_prev];

	free(pter);

	return (ptersvar);
}
