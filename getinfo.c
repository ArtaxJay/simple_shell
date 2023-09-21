#include "shell.h"

/**
 * kill_info_struct - inits struc information_t
 * @info: struct param addr
 */

void kill_info_struct(information_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * init_info_struct - initz struc information_t
 * @info: param struc addr
 * @argvec: the arg vector. NO RETURN
 */

void init_info_struct(information_t *info, char **argvec)
{
	int i;

	i = 0;

	info->fname = argvec[0];

	if (info->arg)
	{
		info->argv = splitstrs(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _duplic_string(info->arg);
				info->argv[1] = NULL;
			}
		}

		while (info->argv && info->argv[i])
			i++;

		info->argc = i;

		repl_tork_alias(info);
		repl_vars_tok_strs(info);
	}
}

/**
 * fr_info_struct - this frees struc information_t fields
 * @info: param struc addr
 * @freedall: set TRUE if all fields are freed
 */

void fr_info_struct(information_t *info, int freedall)
{
	disectfree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (freedall)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			fr_all_node_lists(&(info->env));
		if (info->history)
			fr_all_node_lists(&(info->history));
		if (info->alias)
			fr_all_node_lists(&(info->alias));
		disectfree(info->environ);
			info->environ = NULL;
		freepts((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_ptchars(BUFFER_FLUSH);
	}
}
