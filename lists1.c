#include "shell.h"

/**
 * len_of_lnkd_list - determ dlen linkd--list
 * @hdvar: pter to dfirst-nd
 * Return: ret something
 */

size_t len_of_lnkd_list(const lists_t *hdvar)
{
	size_t countlen;

	for (countlen = 0; hdvar; countlen++)
		hdvar = hdvar->next;

	return (countlen);
}

/**
 * ret_array_of_strs - ret arr of list=>strng
 * @varhd: pter dhead-nd
 * Return: strngs arr
 */

char **ret_array_of_strs(lists_t *varhd)
{
	lists_t *node = varhd;
	size_t iter = len_of_lnkd_list(varhd), seciter;
	char **varstrng;
	char *secstrng;

	if (!varhd || !iter)
		return (NULL);

	varstrng = malloc(sizeof(char *) * (iter + 1));
	if (!varstrng)
		return (NULL);

	for (iter = 0; node; node = node->next, iter++)
	{
		secstrng = malloc(_len_of_str(node->secstrng) + 1);
		if (!secstrng)
		{
			for (seciter = 0; seciter < iter; seciter++)
				free(varstrng[seciter]);
			free(varstrng);
			return (NULL);
		}

		secstrng = _strscopier(secstrng, node->secstrng);
		varstrng[iter] = secstrng;
	}

	varstrng[iter] = NULL;

	return (varstrng);
}


/**
 * prnt_all_elem_lst - will prnt all elemz of d lists_t
 * @dhdnd: pter to dhead-nd
 * Return: ret list-size
 */

size_t prnt_all_elem_lst(const lists_t *dhdnd)
{
	size_t counter;

	for (counter = 0; dhdnd; counter++)
	{
		_pout_std(con_nums(dhdnd->num, 10, 0));
		_ptchars(':');
		_ptchars(' ');
		_pout_std(dhdnd->str ? dhdnd->str : "(nada)");
		_pout_std("\n");
		dhdnd = dhdnd->next;
	}

	return (counter);
}

/**
 * nd_with_prefix_start - prnt d-nd with a prefix
 * @fdnd: pter to d nd-head
 * @ndprefx: search for this arg-str-type
 * @c: d nxt charac after ndprefx to search
 * Return: find nd || NULL
 */

lists_t *nd_with_prefix_start(lists_t *fdnd, char *ndprefx, char c)
{
	char *pter = NULL;

	while (fdnd)
	{
		pter = haystack_needle(fdnd->str, ndprefx);

		if (pter && ((c == -1) || (*pter == c)))
			return (fdnd);

		fdnd = fdnd->next;
	}
	return (NULL);
}

/**
 * gt_index_of_nodes - gts the positions of nds
 * @lshead: pter to dlist-hed
 * @ndpter: pter to dnd
 * Return: index of nd or -1
 */
ssize_t gt_index_of_nodes(lists_t *lshead, lists_t *ndpter)
{
	size_t i = 0;

	while (lshead)
	{
		if (lshead == ndpter)
			return (i);
		lshead = lshead->next;
		i++;
	}
	return (-1);
}
