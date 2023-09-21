#include "shell.h"

/**
 *_eeputts - prnts STD_INPUT strngs
 * @str: strngs to the STD_OUTPUT
 * Return: VOID
 */

void _eeputts(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		_putsfinds(str[i]);
		i++;
	}
}

/**
 * _eputcharr - wrts args `c` to STD_ERR
 * @c: The args charac to be written
 * Return: success = 1.
 */

int _eputcharr(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZES];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZES)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfnd - wrts the args `c` to the given arg `fd`
 * @c: The args charac to be written to `fd`
 * @fd: The arg -- `filedescriptor` to wrt to
 * Return: on success = 1.
 */

int _putsfnd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZES];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZES)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfinds - prnts inputs
 * @str: this arg stores strngs to be printed
 * @fd: fd -- `filedescriptor` to write to
 * Return: returns i -- the numbr of characs prnted
 */

int _putsfinds(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _eeputts(*str++, fd);
	}
	return (i);
}
