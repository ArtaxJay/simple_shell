#include "shell.h"

/**
 * _len_of_str - ret len of strs
 * @checkleng: d str we want to check its len
 * Return: ret len
 */
int _len_of_str(char *checkleng)
{
	int i = 0;

	if (!checkleng)
		return (0);

	while (*checkleng++)
		i++;
	return (i);
}

/**
 * _compstrs - compares of 2-strs.
 * @frstarg: d 1st-str arg
 * @secarg: d 2nd-str arg
 * Return: ret some values as appropriate
 */

int _compstrs(char *frstarg, char *secarg)
{
	while (*frstarg && *secarg)
	{
		if (*frstarg != *secarg)
		{
			return (*frstarg - *secarg);
		}
		secarg++;
		frstarg++;
	}

	if (*frstarg == *secarg)
		return (0);
	else
		return (*secarg > frstarg ? -1 : 1);
}

/**
 * haystack_needle - checks if needle starts with haystack
 * @scrhhay: strn to find
 * @nedeye: substr to find
 * Return: ret addr
 */

char *haystack_needle(const char *scrhhay, const char *nedeye)
{
	while (*nedeye)
	{
		if (*nedeye++ != *scrhhay++)
			return (NULL);
	}
	return ((char *)scrhhay);
}

/**
 * _concatstr - concats 2-strs
 * @destintn: d BUFFER destintn
 * @buffsource: BUFFER source
 * Return: pter 2 buffer destintn
 */

char *_concatstr(char *destintn, char *buffsource)
{
	char *retvalue = destintn;

	while (*destintn)
		destintn++;
	while (*buffsource)
		*destintn++ = *buffsource++;
	*destintn = *buffsource;
	return (retvalue);
}
