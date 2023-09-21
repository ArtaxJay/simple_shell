#include "shell.h"

/**
 * add_nd_to_list_start - append a nd to start of hist-list
 * @ndhead: the addr of pter to the nd HEAD
 * @ndstrfield: dstrng nd field
 * @indxnum: nd indx numb usd by hist-list
 * Return: ret dsize of hist
 */

lists_t *add_nd_to_list_start(lists_t **ndhead,
	const char *ndstrfield, int indxnum)
{
	lists_t *new_head;

	if (!ndhead)
		return (NULL);

	new_head = malloc(sizeof(lists_t));
	if (!new_head)
		return (NULL);

	_memconstbyte((void *)new_head, 0, sizeof(lists_t));
	new_head->indxnum = indxnum;

	if (ndstrfield)
	{
		new_head->ndstrfield = _duplic_string(ndstrfield);
		if (!new_head->ndstrfield)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *ndhead;
	*ndhead = new_head;

	return (new_head);
}

/**
 * add_nd_to_list_end - adds a node to the end of the list
 * @ndhead: pter to d nd-head addr
 * @ndstrfield: pter for the nd field
 * @ndindxnum: nd indx for hist-list
 * Return: dlist size
 */

lists_t *add_nd_to_list_end(lists_t **ndhead,
	const char *ndstrfield, int ndindxnum)
{
	lists_t *new_node, *node;

	if (!ndhead)
		return (NULL);

	node = *ndhead;

	new_node = malloc(sizeof(lists_t));
	if (!new_node)
		return (NULL);

	_memconstbyte((void *)new_node, 0, sizeof(lists_t));
	new_node->ndindxnum = ndindxnum;

	if (ndstrfield)
	{
		new_node->ndstrfield = _duplic_string(ndstrfield);
		if (!new_node->ndstrfield)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;

		node->next = new_node;
	}
	else
		*ndhead = new_node;

	return (new_node);
}

/**
 * prnt_strelem_of_list - prnts dstr elem lists_t linked--list
 * @ndhd: pter for dfirst-nd
 * Return: dlist-size
 */

size_t prnt_strelem_of_list(const lists_t *ndhd)
{
	size_t iterator;

	for (iterator = 0; ndhd; iterator++)
	{
		_pout_std(ndhd->str ? ndhd->str : "(nada)");
		_pout_std("\n");
		ndhd = ndhd->next;
	}

	return (iterator);
}

/**
 * del_dgiven_node - rem-permanently nd at an index
 * @ndhead: arg-pter addr to dfirst-nd
 * @delnd: dindx nd 2 delet
 * Return: always return
 */

int del_dgiven_node(lists_t **ndhead, unsigned int delnd)
{
	lists_t *node, *prev_node;
	unsigned int iterater = 0;

	if (!ndhead || !*ndhead)
		return (0);

	if (!delnd)
	{
		node = *ndhead;
		*ndhead = (*ndhead)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *ndhead;

	while (node)
	{
		if (iterater == delnd)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		iterater++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * fr_all_node_lists - set-free all nds
 * @nd_head: pter to d nd-head
 * Return: VOID
 */

void fr_all_node_lists(lists_t **nd_head)
{
	lists_t *node, *next_node, *head;

	if (!nd_head || !*nd_head)
		return;
	head = *nd_head;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*nd_head = NULL;
}
