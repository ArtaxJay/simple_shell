#include "shell.h"

/**
 * _prntcurenvvar - this prnts the currnt envn
 * @info: struc maintains constant protos
 * Return: always success
 */

int _prntcurenvvar(information_t *info)
{
	prnt_strelem_of_list(info->env);
	return (0);
}

/**
 * _gtenvvarval - this gets vals envn vars
 * @info: struc to hold potent args
 * @name: envn var name
 * Return: on success - returns the envn value
 */

char *_gtenvvarval(information_t *info, const char *name)
{
	lists_t *node = info->env;
	char *p;

	while (node)
	{
		p = haystack_needle(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _initenvvar - creates new envn vars and can modify existng ones
 * @info: structs hold info
 *  Return: always 0
 */

int _initenvvar(information_t *info)
{
	if (info->argc != 3)
	{
		_eputcharr("Wrong numb of args\n");
		return (1);
	}
	if (_initnewvar(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _remenvvar - clears envm vars
 * @info: stores struct info
 *  Return: sometimes 0 or 1
 */

int _remenvvar(information_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputcharr("Add some more args.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_remenvvariable(info, info->argv[i]);

	return (0);
}

/**
 * add_to_env_lst - adds envn linked-list
 * @info: maintains const funct protos
 * Return: always 0
 */
int add_to_env_lst(information_t *info)
{
	lists_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nd_to_list_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
