#include "shell.h"

/**
 * get_envment - ret strng arr cpy of our envnment vars
 * @info: struct var
 * Return: only success
 */

char **get_envment(information_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = ret_array_of_strs(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _remenvvariable - rem envnment vars
 * @info: struc param
 * @evnvar: strng env vars
 *  Return: always -- 1 on delete, 0 otherwise
 */

int _remenvvariable(information_t *info, char *evnvar)
{
	lists_t *node = info->env;
	size_t iterator;
	char *ptrs;

	if (!node || !evnvar)
		return (0);

	for (iterator = 0; node; iterator++)
	{
		ptrs = haystack_needle(node->str, evnvar);

		if (ptrs && *ptrs == '=')
		{
			info->env_changed = del_dgiven_node(&(info->env), iterator);
			iterator = 0;
			node = info->env;
			continue;
		}
		node = node->next;
	}

	return (info->env_changed);
}

/**
 * _initnewvar - init new env vars || modify existng ones
 * @info: param for struct
 * @strenvvar: strng env var properties
 * @strenvval: strng env vars vals
 *  Return: if success = 0
 */

int _initnewvar(information_t *info, char *strenvvar, char *strenvval)
{
	char *bffer = NULL;
	lists_t *node;
	char *ptrz;

	if (!strenvvar || !strenvval)
		return (0);

	bffer = malloc(_len_of_str(strenvvar) + _len_of_str(strenvval) + 2);
	if (!bffer)
		return (1);
	_strscopier(bffer, strenvvar);
	_concatstr(bffer, "=");
	_concatstr(bffer, strenvval);
	node = info->env;

	while (node)
	{
		ptrz = haystack_needle(node->str, strenvvar);
		if (ptrz && *ptrz == '=')
		{
			free(node->str);
			node->str = bffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_nd_to_list_end(&(info->env), bffer, 0);
	free(bffer);
	info->env_changed = 1;

	return (0);
}
