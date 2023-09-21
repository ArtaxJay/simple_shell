#include "shell.h"

/**
 * _lsthistory - displays the history list
 * @info: A potent arg is saved here
 *  Return: returns always success
 */

int _lsthistory(information_t *info)
{
	prnt_all_elem_lst(info->history);
	return (0);
}

/**
 * remv_alias - the funct sets aliases to strs
 * @info: struct param
 * @str: stores the str alias
 * Return: 0 on success, 1 on error
 */

int remv_alias(information_t *info, char *str)
{
	char *p, charac;
	int ret_res;

	p = _loc_char(str, '=');
	if (!p)
		return (1);
	charac = *p;
	*p = 0;
	ret_res = del_dgiven_node(&(info->alias),
		gt_index_of_nodes(info->alias, nd_with_prefix_start(info->alias, str, -1)));
	*p = charac;
	return (ret_res);
}

/**
 * create_new_alias - creates alias str
 * @info: struct param
 * @str: the alias strs
 * Return: 1 on error, 0 on success
 */

int create_new_alias(information_t *info, char *str)
{
	char *p;

	p = _loc_char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remv_alias(info, str));

	remv_alias(info, str);
	return (add_nd_to_list_end(&(info->alias), str, 0) == NULL);
}

/**
 * alias_prnter - the func prnts aliases strngs
 * @node: the node for aliases
 * Return: Always 1 on error, 0 on success
 */

int alias_prnter(lists_t *node)
{
	char *p = NULL, *alis = NULL;

	if (node)
	{
		p = _loc_char(node->str, '=');
		for (alis = node->str; alis <= p; alis++)
			_ptchars(*alis);
		_ptchars('\'');
		_pout_std(p + 1);
		_pout_std("'\n");
		return (0);
	}
	return (1);
}

/**
 * _mimicslibalias - performs the same func as the builtin alias
 * @info: potent args stored in a struc
 *  Return: on success
 */

int _mimicslibalias(information_t *info)
{
	int i = 0;
	char *p = NULL;
	lists_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_prnter(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
	p = _loc_char(info->argv[i], '=');
	if (p)
		create_new_alias(info, info->argv[i]);
	else
		alias_prnter(nd_with_prefix_start(info->alias, info->argv[i], '='));
	}

	return (0);
}
