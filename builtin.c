#include "shell.h"

/**
 * _killshell - terminates the shell program
 * @info: struct used to maintain constant func protos
 *  Return: terminates on specific statuses
 */

int _killshell(information_t *info)
{
	int termicheck;

	if (info->argv[1])
	{
		termicheck = _str_to_int(info->argv[1]);
		if (termicheck == -1)
		{
			info->status = 2;
			prnt_err_msg(info, "Wrong number: ");
			_eputcharr(info->argv[1]);
			_putsfinds('\n');
			return (1);
		}
		info->err_num = _str_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _chgcurdir - chngs the current working directory
 * @info: A struct for holding potent args
 *  Return: On success - always 0
 */
int _chgcurdir(information_t *info)
{
	char *s, *drect, buffer[1024];
	int chngdrec;

	s = getcwd(buffer, 1024);
	if (!s)
		_pout_std("DO: >>getcwd error msg<<\n");
	if (!info->argv[1])
	{
		drect = _gtenvvarval(info, "HOME=");
		if (!drect)
			chngdrec = chdir((drect = _gtenvvarval(info, "PWD=")) ? drect : "/");
		else
			chngdrec = chdir(drect);
	}
	else if (_compstrs(info->argv[1], "-") == 0)
	{
		if (!_gtenvvarval(info, "OLDPWD="))
		{
			_pout_std(s);
			_ptchars('\n');
			return (1);
		}
		_pout_std(_gtenvvarval(info, "OLDPWD=")), _ptchars('\n');
		chngdrec = chdir((drect = _gtenvvarval(info, "OLDPWD=")) ? drect : "/");
	}
	else
		chngdrec = chdir(info->argv[1]);
	if (chngdrec == -1)
	{
		prnt_err_msg(info, "can't cd to ");
		_eputcharr(info->argv[1]), _putsfinds('\n');
	}
	else
	{
		_initnewvar(info, "OLDPWD", _gtenvvarval(info, "PWD="));
		_initnewvar(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _chngdir - chngs the current working direc
 * @info: This struct holds potent args
 *  Return: On success - always 0
 */

int _chngdir(information_t *info)
{
	char **arr_arg;

	arr_arg = info->argv;
	_pout_std("Help call. The func you seek is not implemented yet \n");
	if (0)
	{
		_pout_std(*arr_arg);
	}
	return (0);
}
