#include "shell.h"

/**
 * chck_chain_delim - checks whether d curnt char in buffer is a chain-delim
 * @info: arg-param struc
 * @buffer: char inside buffer
 * @addrinbuf: d addr to d curnt posit in buffer
 * Return: 1 is success, 0 is failed
 */

int chck_chain_delim(information_t *info, char *buffer, size_t *addrinbuf)
{
	size_t varj = *addrinbuf;

	if (buffer[varj] == '|' && buffer[varj + 1] == '|')
	{
		buffer[varj] = 0;
		varj++;
		info->cmd_buf_type = COMMAND_LOGICAL_OR;
	}
	else if (buffer[varj] == '&' && buffer[varj + 1] == '&')
	{
		buffer[varj] = 0;
		varj++;
		info->cmd_buf_type = COMMAND_LOGICAL_AND;
	}
	else if (buffer[varj] == ';')
	{
		buffer[varj] = 0;
		info->cmd_buf_type = COMMAND_CHAINED;
	}
	else
		return (0);

	*addrinbuf = varj;

	return (1);
}

/**
 * chks_for_chain_status - asks whether to cont. chaining basd on d laststatus
 * @info: d param-arg struct
 * @varbuffer: d buffer arg
 * @varaddrpo: addr to d curnt position in buffer
 * @varindx: first index position in bufffer
 * @varlen: varlen of buffer
 * Return: Void
 */

void chks_for_chain_status(information_t *info, char *varbuffer,
	size_t *varaddrpo, size_t varindx, size_t varlen)
{
	size_t varj = *varaddrpo;

	if (info->cmd_buf_type == COMMAND_LOGICAL_AND)
	{
		if (info->status)
		{
			varj = varlen;
			varbuffer[varindx] = 0;
		}
	}

	if (info->cmd_buf_type == COMMAND_LOGICAL_OR)
	{
		if (!info->status)
		{
			varj = varlen;
			varbuffer[varindx] = 0;
		}
	}

	*varaddrpo = varj;
}

/**
 * repl_tork_alias - replac aliases in d TOKENIZED strs
 * @info: d struc param-args
 * Return: always succesfull and 0 if failed
 */

int repl_tork_alias(information_t *info)
{
	int iter;
	lists_t *node;
	char *pter;

	iter = 0;
	while (iter < 10)
	{
		node = nd_with_prefix_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		pter = _loc_char(node->str, '=');
		if (!pter)
			return (0);

		pter = _duplic_string(pter + 1);
		if (!pter)
			return (0);

		info->argv[0] = pter;

		iter++;
	}

	return (1);
}

/**
 * repl_vars_tok_strs - replac vars in d TOKENIZED strs
 * @info: arg-param struc
 * Return: always successful
 */

int repl_vars_tok_strs(information_t *info)
{
	int iterator;
	lists_t *node;

	iterator = 0;
	while (info->argv[iterator])
	{
		if (info->argv[iterator][0] != '$' || !info->argv[iterator][1])
			continue;

		if (!_compstrs(info->argv[iterator], "$?"))
		{
			repl_strngs(&(info->argv[iterator]),
				_duplic_string(con_nums(info->status, 10, 0)));
			continue;
		}
		if (!_compstrs(info->argv[iterator], "$$"))
		{
			repl_strngs(&(info->argv[iterator]),
				_duplic_string(con_nums(getpid(), 10, 0)));
			continue;
		}
		node = nd_with_prefix_start(info->env, &info->argv[iterator][1], '=');
		if (node)
		{
			repl_strngs(&(info->argv[iterator]),
				_duplic_string(_loc_char(node->str, '=') + 1));
			continue;
		}
		repl_strngs(&info->argv[iterator], _duplic_string(""));

		iterator++;
	}

	return (0);
}

/**
 * repl_strngs - free-replac strs
 * @prev: d addr of prev strs
 * @brnew: d brand brnew strs
 * Return: ret 1
 */

int repl_strngs(char **prev, char *brnew)
{
	free(*prev);
	*prev = brnew;

	return (1);
}
