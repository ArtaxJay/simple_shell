#include "shell.h"

/**
 * gt_hist_fle - the func gts the hist file
 * @info: struc param
 * Return: on success = 0
 */

char *gt_hist_fle(information_t *info)
{
	char *gtbuffer, *gtdir;

	gtdir = _gtenvvarval(info, "HOME=");
	if (!gtdir)
		return (NULL);
	gtbuffer = malloc(sizeof(char) *
	(_len_of_str(gtdir) + _len_of_str(FILE_HISTORY) + 2));
	if (!gtbuffer)
		return (NULL);
	gtbuffer[0] = 0;
	_strscopier(gtbuffer, gtdir);
	_concatstr(gtbuffer, "/");
	_concatstr(gtbuffer, FILE_HISTORY);
	return (gtbuffer);
}

/**
 * wrt_hist - wrt hist
 * @info: the arg param struc
 * Return: 1 if successful, and -1
 */

int wrt_hist(information_t *info)
{
	ssize_t filed;
	char *fname = gt_hist_fle(info);
	lists_t *node = NULL;

	if (!fname)
		return (-1);

	filed = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (filed == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfnd(node->str, filed);
		_eeputts('\n', filed);
	}
	_eeputts(BUFFER_FLUSH, filed);
	close(filed);
	return (1);
}

/**
 * rd_hist - rds shell hist cmds frm file
 * @info: arg-param struc
 * Return: returns the shell hist value
 */

int rd_hist(information_t *info)
{
	int i, lthist = 0, numline = 0;
	ssize_t fidir, redleng, file_size = 0;
	struct stat st;
	char *bvar = NULL, *flnames = gt_hist_fle(info);

	if (!flnames)
		return (0);
	fidir = open(flnames, O_RDONLY);
	free(flnames);
	if (fidir == -1)
		return (0);
	if (!fstat(fidir, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	bvar = malloc(sizeof(char) * (file_size + 1));
	if (!bvar)
		return (0);
	redleng = read(fidir, bvar, file_size);
	bvar[file_size] = 0;
	if (redleng <= 0)
		return (free(bvar), 0);
	close(fidir);
	for (i = 0; i < file_size; i++)
	{
		if (bvar[i] == '\n')
		{
			bvar[i] = 0;
			add_entry_tohist(info, bvar + lthist, numline++);
			lthist = i + 1;
		}
	}
	if (lthist != i)
		add_entry_tohist(info, bvar + lthist, numline++);
	free(bvar);
	info->histcount = numline;
	while (info->histcount-- >= MAXIMUM_HISTORY_NUMBER)
		del_dgiven_node(&(info->history), 0);
	chng_hist_num(info);
	return (info->histcount);
}

/**
 * add_entry_tohist - append new cmds to hist
 * @info: the arg-param struct
 * @bhere: the BUFFER
 * @countline: the hist counter
 * Return: on success 0
 */

int add_entry_tohist(information_t *info, char *bhere, int countline)
{
	lists_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}

	add_nd_to_list_end(&node, bhere, countline);

	if (!info->history)
	{
		info->history = node;
	}

	return (0);
}

/**
 * chng_hist_num - reorder the hist-list after adjusment
 * @info: the arg-param for struc
 * Return: ret the new hist-list
 */

int chng_hist_num(information_t *info)
{
	lists_t *node = info->history;
	int iterator = 0;

	while (node)
	{
		node->num = iterator++;
		node = node->next;
	}

	return (info->histcount = iterator);
}
