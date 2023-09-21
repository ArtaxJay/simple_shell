#include "shell.h"

/**
 **_copy_strns - the func copies strs
 *@dstnatn: the destination the strs are to be copied to
 *@source: pointer source strs
 *@amnt: the number of characs to copy
 *Return: returns the concatd strs
 */

char *_copy_strns(char *dstnatn, char *source, int amnt)
{
	int ivar, jvar;
	char *strsconcat = dstnatn;

	for (ivar = 0; source[ivar] != '\0' && ivar < amnt - 1; ivar++)
		dstnatn[ivar] = source[ivar];

	if (ivar < amnt)
	{
		jvar = ivar;
		while (jvar < amnt)
		{
			dstnatn[jvar] = '\0';
			jvar++;
		}
	}
	return (strsconcat);
}

/**
 **_add_two_strs - concatenates two strings
 *@firststr: the first string
 *@secstr: the second string
 *@byteamnt: the amount of bytes to be maximally used
 *Return: returns concat strs
 */

char *_add_two_strs(char *firststr, char *secstr, int byteamnt)
{
	int itera, jvar;
	char *strsconcat = firststr;

	for (itera = 0; firststr[itera] != '\0'; itera++)
		;

	for (jvar = 0; secstr[jvar] != '\0' && jvar < byteamnt; jvar++)
	{
		firststr[itera] = secstr[jvar];
		itera++;
	}

	if (jvar < byteamnt)
		firststr[itera] = '\0';

	return (strsconcat);
}

/**
 **_loc_char - finds characs in passed-parsed strs
 *@strparsed: passed strng to parse
 *@charlk: charac to find
 *Return: --strparsed-- ptr to the mem area
 */

char *_loc_char(char *strparsed, char charlk)
{
	do {
		if (*strparsed == charlk)
			return (strparsed);
	} while (*strparsed++ != '\0');

	return (NULL);
}
