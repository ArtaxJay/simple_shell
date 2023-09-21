#include "shell.h"

/**
 * shellhsh - shll lOOp
 * @info: ret struct arg-param
 * @vecargu: vector arg-param
 * Return: ret whatsoever
 */

int shellhsh(information_t *info, char **vecargu)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		kill_info_struct(info);
		if (interacshell(info))
			_pout_std("$ ");

		_putsfinds(BUFFER_FLUSH);
		r = gets_line(info);

		if (r != -1)
		{
			init_info_struct(info, vecargu);
			builtin_ret = finds_cmds_builtins(info);
			if (builtin_ret == -1)
				find_command_path(info);
		}
		else if (interacshell(info))
			_ptchars('\n');

		fr_info_struct(info, 0);
	}

	wrt_hist(info);
	fr_info_struct(info, 1);

	if (!interacshell(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * finds_cmds_builtins - look for cmd builtins
 * @info: struc param-arg
 * Return: ret all err msgs
 */

int finds_cmds_builtins(information_t *info)
{
	int foriter = 0, built_in_ret = -1;

	builtins_tbls builtintbl[] = {
		{"exit", _killshell},
		{"env", _prntcurenvvar},
		{"help", _chngdir},
		{"history", _lsthistory},
		{"setenv", _initenvvar},
		{"unsetenv", _remenvvar},
		{"cd", _chgcurdir},
		{"alias", _mimicslibalias},
		{NULL, NULL}
	};

	while (builtintbl[foriter].type)
	{
		if (_compstrs(info->argv[0], builtintbl[foriter].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[foriter].func(info);
			break;
		}
		foriter++;
	}

	return (built_in_ret);
}

/**
 * find_command_path - look for CLI cmds in PATH
 * @info: struc param-arg
 * Return: ret VOID
 */

void find_command_path(information_t *info)
{
	char *pthway = NULL;
	int firstiter = 0, seciter;

	info->pthway = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	while (seciter = 0; info->arg[firstiter])
	{
		if (!chk_for_delim(info->arg[firstiter], " \t\n"))
			seciter++;
		firstiter++
	}

	if (!seciter)
		return;

	pthway = search_path(info, _gtenvvarval(info, "PATH="), info->argv[0]);
	if (pthway)
	{
		info->pthway = pthway;
		forks_exec_cmd(info);
	}
	else
	{
		if ((interacshell(info) || _gtenvvarval(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			forks_exec_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			prnt_err_msg(info, "not found\n");
		}
	}
}

/**
 * forks_exec_cmd - frks exec threads to run CLI cmds
 * @info: arg-param struc
 * Return: ret VOID
 */

void forks_exec_cmd(information_t *info)
{
	pid_t progeny_pid;

	progeny_pid = fork();
	if (progeny_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (progeny_pid == 0)
	{
		if (execve(info->path, info->argv, get_envment(info)) == -1)
		{
			fr_info_struct(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prnt_err_msg(info, "Permission denied\n");
		}
	}
}
