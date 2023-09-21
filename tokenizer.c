#include "shell.h"

/**
 * **splitstrs - divides strs in2 words
 * @dstrs: d input strs to be splitted
 * @delim: delim delimeter strs to be left-out
 * Return: pter to strs
 */

char **splitstrs(char *dstrs, char *delim)
{
	int iterater, varj, vark, varm, spltword = 0;
	char **reslt;

	if (dstrs == NULL || dstrs[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (iterater = 0; dstrs[iterater] != '\0'; iterater++)
		if (!chk_for_delim(dstrs[iterater],
	delim) && (chk_for_delim(dstrs[iterater + 1],
	delim) || !dstrs[iterater + 1]))
			spltword++;

	if (spltword == 0)
		return (NULL);
	reslt = malloc((1 + spltword) * sizeof(char *));
	if (!reslt)
		return (NULL);
	for (iterater = 0, varj = 0; varj < spltword; varj++)
	{
		while (chk_for_delim(dstrs[iterater], delim))
			iterater++;
		vark = 0;
		while (!chk_for_delim(dstrs[iterater + vark],
	delim) && dstrs[iterater + vark])
			vark++;
		reslt[varj] = malloc((vark + 1) * sizeof(char));
		if (!reslt[varj])
		{
			for (vark = 0; vark < varj; vark++)
				free(reslt[vark]);
			free(reslt);
			return (NULL);
		}
		for (varm = 0; varm < vark; varm++)
			reslt[varj][varm] = dstrs[iterater++];
		reslt[varj][varm] = 0;
	}
	reslt[varj] = NULL;
	return (reslt);
}

/**
 * **splitstrns - divides strs into words
 * @dstrs: d input strs
 * @delimvar: delim var
 * Return: ret whatever
 */
char **splitstrns(char *dstrs, char delimvar)
{
	int iterator, varj, vark, varm, spltword = 0;
	char **reslt;

	if (dstrs == NULL || dstrs[0] == 0)
		return (NULL);
	for (iterator = 0; dstrs[iterator] != '\0'; iterator++)
		if ((dstrs[iterator] != delimvar && dstrs[iterator + 1] == delimvar) ||
		    (dstrs[iterator] != delimvar && !dstrs[iterator + 1]) ||
		    dstrs[iterator + 1] == delimvar)
			spltword++;
	if (spltword == 0)
		return (NULL);
	reslt = malloc((1 + spltword) * sizeof(char *));
	if (!reslt)
		return (NULL);
	for (iterator = 0, varj = 0; varj < spltword; varj++)
	{
		while (dstrs[iterator] == delimvar && dstrs[iterator] != delimvar)
			iterator++;
		vark = 0;
		while (dstrs[iterator + vark] != delimvar && dstrs[iterator + vark] &&
	dstrs[iterator + vark] != delimvar)
			vark++;
		reslt[varj] = malloc((vark + 1) * sizeof(char));
		if (!reslt[varj])
		{
			for (vark = 0; vark < varj; vark++)
				free(reslt[vark]);
			free(reslt);
			return (NULL);
		}
		for (varm = 0; varm < vark; varm++)
			reslt[varj][varm] = dstrs[iterator++];
		reslt[varj][varm] = 0;
	}
	reslt[varj] = NULL;
	return (reslt);
}
