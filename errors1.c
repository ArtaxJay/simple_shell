#include "shell.h"

/**
 * _str_to_int - this funct will convert strs to ints
 * @s: strs to convert
 * Return: returns 0, 1, -1 error
 */

int _str_to_int(char *s)
{
	int iterator = 0;
	unsigned long int anwser = 0;

	if (*s == '+')
		s++;

	for (iterator = 0;  s[iterator] != '\0'; iterator++)
	{
		if (s[iterator] >= '0' && s[iterator] <= '9')
		{
			anwser *= 10;
			anwser += (s[iterator] - '0');
			if (anwser > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (anwser);
}

/**
 * prnt_err_msg - prints err msgs
 * @info: the info struct
 * @estr: str that stores specified err-type
 * Return: 0, 1, -1 on err
 */

void prnt_err_msg(information_t *info, char *estr)
{
	_eputcharr(info->fname);
	_eputcharr(": ");
	prnt_dec_num(info->line_count, STDERR_FILENO);
	_eputcharr(": ");
	_eputcharr(info->argv[0]);
	_eputcharr(": ");
	_eputcharr(estr);
}

/**
 * prnt_dec_num - funct prints a decimal numb
 * @input: the inpt to be printed
 * @fd: fd `filedescriptor` to be printed
 * Return: returns an int
 */

int prnt_dec_num(int input, int fd)
{
	int (*__ptchars)(char) = _ptchars;
	int i, counter_var = 0;
	unsigned int temp_curr, current;

	if (fd == STDERR_FILENO)
		__ptchars = _eputchar;
	if (input < 0)
	{
		temp_curr = -input;
		__ptchars('-');
		counter_var++;
	}
	else
		temp_curr = input;
	current = temp_curr;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (temp_curr / i)
		{
			__ptchars('0' + current / i);
			counter_var++;
		}
		current %= i;
	}
	__ptchars('0' + current);
	counter_var++;

	return (counter_var);
}

/**
 * con_nums - itoa look-alike funct
 * @longnumb: LONG INT VARIABLE
 * @base_val: base
 * @signal_flags: argument flags
 *
 * Return: string
 */
char *con_nums(long int longnumb, int base_val, int signal_flags)
{
	static char *array;
	static char buffer[50];
	char signals = 0;
	char *pointer;
	unsigned long varnum = longnumb;

	if (!(signal_flags & CONVERT_FROM_UNSIGNED) && longnumb < 0)
	{
		varnum = -longnumb;
		signals = '-';

	}
	array = signal_flags & CONVERT_TO_LOWERCASE ?
	"0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = array[varnum % base_val];
		varnum /= base_val;
	} while (varnum != 0);

	if (signals)
		*--pointer = signals;
	return (pointer);
}

/**
 * rem_commts - repl first '#' with '\0'
 * @buffer: add to str to modify
 * Return: returns VOID
 */

void rem_commts(char *buffer)
{
	int iterat;

	for (iterat = 0; buffer[iterat] != '\0'; iterat++)
		if (buffer[iterat] == '#' && (!iterat || buffer[iterat - 1] == ' '))
		{
			buffer[iterat] = '\0';
			break;
		}
}
