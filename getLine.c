#include "shell.h"

/**
 * input_buf - the buf chained comds
 * @info: param struc var
 * @varbuffer: the addr of buffer
 * @varlen: stores the addr of the lenght var
 * Return: returns the read bytes
 */

ssize_t input_buf(information_t *info, char **varbuffer, size_t *varlen)
{
	size_t pt_len = 0;
	ssize_t valread = 0;

	if (!*varlen)
	{
		free(*varbuffer);
		*varbuffer = NULL;
		signal(SIGINT, handlesignals);
#if GETLINE_USED
		valread = getline(varbuffer, &pt_len, stdin);
#else
		valread = _myverofgetline(info, varbuffer, &pt_len);
#endif
		if (valread > 0)
		{
			if ((*varbuffer)[valread - 1] == '\n')
			{
				(*varbuffer)[valread - 1] = '\0';
				valread--;
			}

			info->linecount_flag = 1;
			rem_commts(*varbuffer);

			add_entry_tohist(info, *varbuffer, info->histcount++);
			{
				*varlen = valread;
				info->cmd_buf = varbuffer;
			}
		}
	}

	return (valread);
}

/**
 * gets_line - will get lines - the `\n`
 * @info: struc param arg
 * Return: also returns the bytes read
 */

ssize_t gets_line(information_t *info)
{
	static char *varbuffer;
	static size_t iterator, varj, length;
	ssize_t byte_read = 0;
	char **ptrs_buffer = &(info->arg), *singleptr;

	_ptchars(BUFFER_FLUSH);
	byte_read = input_buf(info, &varbuffer, &length);
	if (byte_read == -1)
		return (-1);
	if (length)
	{
		varj = iterator;
		singleptr = varbuffer + iterator;

		chks_for_chain_status(info, varbuffer, &varj, iterator, length);
		while (varj < length)
		{
			if (chck_chain_delim(info, varbuffer, &varj))
				break;
			varj++;
		}

		iterator = varj + 1;
		if (iterator >= length)
		{
			iterator = length = 0;
			info->cmd_buf_type = COMMAND_NORMAL;
		}

		*ptrs_buffer = singleptr;
		return (_len_of_str(singleptr));
	}

	*ptrs_buffer = varbuffer;
	return (byte_read);
}

/**
 * read_buf - will be reading buffers
 * @info: struct arg parameter
 * @tbuffer: the BUFFER
 * @b_size: BUFFER_SIZE
 * Return: returns read_bytes
 */

ssize_t read_buf(information_t *info, char *tbuffer, size_t *b_size)
{
	ssize_t r_bytes = 0;

	if (*b_size)
		return (0);
	r_bytes = read(info->readfd, tbuffer, READ_BUFFER_SIZE);
	if (r_bytes >= 0)
		*b_size = r_bytes;
	return (r_bytes);
}

/**
 * _myverofgetline - will get next-line of input from STD_INPUT
 * @info: struc param
 * @ptertobufs: the addr of ptrs to buffers
 * @size_leng: the size of pre_allocated ptrs to buffers
 * Return: returns the SIZE
 */

int _myverofgetline(information_t *info, char **ptertobufs, size_t *size_leng)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t itrate, sec_len;

	ssize_t will_read = 0, sizeonly = 0;
	size_t sec_itrater;

	char *locptr = NULL, *fndpter = NULL, *charac;

	locptr = *ptertobufs;

	if (locptr && size_leng)
		sizeonly = *size_leng;

	if (itrate == sec_len)
		itrate = sec_len = 0;

	will_read = read_buf(info, buf, &sec_len);

	if (will_read == -1 || (will_read == 0 && sec_len == 0))
		return (-1);

	charac = _loc_char(buf + itrate, '\n');

	sec_itrater = charac ? 1 + (unsigned int)(charac - buf) : sec_len;

	fndpter = _my_realloc(locptr, sizeonly,
	sizeonly ? sizeonly + sec_itrater : sec_itrater + 1);
	if (!fndpter)
		return (locptr ? free(locptr), -1 : -1);
	if (sizeonly)
		_add_two_strs(fndpter, buf + itrate, sec_itrater - itrate);
	else
		_copy_strns(fndpter, buf + itrate, sec_itrater - itrate + 1);
	sizeonly += sec_itrater - itrate;
	itrate = sec_itrater;
	locptr = fndpter;
	if (size_leng)
		*size_leng = sizeonly;
	*ptertobufs = locptr;
	return (sizeonly);
}

/**
 * handlesignals - prevents ctrl-C frm STD_INPUT
 * @val_of_signal: signal`s num value
 * Return: NOTHING to RETURN
 */

void handlesignals(__attribute__((unused))int val_of_signal)
{
	_pout_std("\n");
	_pout_std("$ ");
	_ptchars(BUFFER_FLUSH);
}
