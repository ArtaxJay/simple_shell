#include "shell.h"

/**
 * _strscopier - func copies charac by strs
 * @whereto: d destintn to str to
 * @fromwhere: d str receiver
 * Return: pter to destintn
 */

char *_strscopier(char *whereto, char *fromwhere)
{
	int iterator;

	if (fromwhere == 0 || whereto == fromwhere)
		return (whereto);

	for (iterator = 0; fromwhere[iterator]; iterator++)
		whereto[iterator] = fromwhere[iterator];

	whereto[iterator] = 0;
	return (whereto);
}

/**
 * _duplic_string - duplic strs
 * @dstrs: dstrs to duplic
 * Return: ret pter to the duplic strs
 */

char *_duplic_string(const char *dstrs)
{
	int varlen = 0;
	char *valret;

	if (dstrs == NULL)
		return (NULL);

	while (*dstrs++)
		varlen++;

	valret = malloc(sizeof(char) * (varlen + 1));
	if (!valret)
		return (NULL);

	for (varlen++; varlen--;)
		valret[varlen] = *--dstrs;

	return (valret);
}

/**
 *_pout_std - pouts some strs input
 *@dstrs: dstrs to be prntd
 * Return: VOID
 */

void _pout_std(char *dstrs)
{
	int iterater;

	if (!dstrs)
		return;

	for (iterater = 0; dstrs[iterater] != '\0'; iterater++)
	{
		_ptchars(dstrs[iterater]);
	}
}

/**
 * _ptchars - wrts d charac to d STD_OUTPUT
 * @charac: charac to BE prntd
 * Return: On success 1
 */

int _ptchars(char charac)
{
	static int iterator;
	static char buf[WRITE_BUFFER_SIZES];

	if (charac == BUFFER_FLUSH || iterator >= WRITE_BUFFER_SIZES)
	{
		write(1, buf, iterator);
		iterator = 0;
	}

	if (charac != BUFFER_FLUSH)
		buf[iterator++] = charac;
	return (1);
}
