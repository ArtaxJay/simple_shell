#include "shell.h"

/**
 * is_command - determs if cmds || files are exec or avable in /bin
 * @paraminfo: param for struc
 * @pthway: dpath 2 dfile
 * Return: on success = 1, if not = 0
 */

int is_command(information_t *paraminfo, char *pthway)
{
	struct stat st;

	(void)paraminfo;
	if (!pthway || stat(pthway, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - findz dupl charac
 * @pathstr: d PATHWAY 2 dstrng
 * @indxstart: d first/startng indx
 * @indxstop: d last/stoppng indx
 * Return: ret pter to new
 */

char *duplicate_chars(char *pathstr, int indxstart, int indxstop)
{
	static char bufmaxsize[1024];
	int frtiter = 0, seciter;

	seciter = 0
	while (frtiter = indxstart; frtiter < indxstop)
	{
		if (pathstr[frtiter] != ':')
		{
			bufmaxsize[seciter++] = pathstr[frtiter];
		}
		frtiter++
	}

	bufmaxsize[seciter] = 0;
	return (bufmaxsize);
}

/**
 * search_path - finds dcurrent cmd in d PATH strng
 * @strucparam: struc param
 * @pterpathway: PATHWAY to strng
 * @clicmd: cmd to search for in /bin
 * Return: whole PATHWAY to cmd if found || NULL
 */

char *search_path(information_t *strucparam, char *pterpathway, char *clicmd)
{
	int counter;
	int positn = 0;
	char *pthway;

	if (!pterpathway)
		return (NULL);

	if ((_len_of_str(clicmd) > 2) && haystack_needle(clicmd, "./"))
	{
		if (is_command(strucparam, clicmd))
			return (clicmd);
	}

	for (counter = 0; TRUE; counter++)
	{
		if (!pterpathway[counter] || pterpathway[counter] == ':')
		{
			pthway = duplicate_chars(pterpathway, positn, counter);

			if (!*pthway)
				_concatstr(pthway, clicmd);
			else
			{
				_concatstr(pthway, "/");
				_concatstr(pthway, clicmd);
			}

			if (is_command(strucparam, pthway))
				return (pthway);

			if (!pterpathway[counter])
				break;

			positn = counter;
		}
	}
	return (NULL);
}
