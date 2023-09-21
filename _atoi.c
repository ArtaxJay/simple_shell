#include "shell.h"

/**
 * interacshell - Will return `TRUE` if shell is in INTERACTIVE MODE
 * @info: the address to the information_t structure
 * Return: returns 1 if INTERACTIVE MODE successfully, 0 if failed
 */

int interacshell(information_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * chk_for_delim - This func checks if a charac is a delimetre
 * @c: the argument char to be checked
 * @delim: the delimetre str argument
 * Return: returns 1 if TRUE,while 0 is returned if FALSE
 */
int chk_for_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 *_chk_for_alpha - The function will check for alphabe charac
 *@c: The alphabe charac to input
 *Return: 1 if c is an alphabe, return 0 in case of otherwise
 */

int _chk_for_alpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/**
 *_conv_str_int - This funct converts strs to ints
 *@s: holds the var strs to be converted to ints
 *Return: NULL (0) if no numbers in str
 */

int _conv_str_int(char *s)
{
	int i;
	int signal = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		{
		signal *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (signal == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}
	return (output);
}
