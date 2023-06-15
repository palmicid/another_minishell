/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:19:23 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 17:24:45 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_newpwdenv(int oldpwd, int pwd)
{
	char	*curdir;

	curdir = getcwd(NULL, 0);
	if ((oldpwd != -1) && (pwd == -1))
	{
		free(g_data.env[oldpwd]);
		g_data.env[oldpwd] = ft_strjoin("OLDPWD=", "");
	}
	else if ((oldpwd == -1) && (pwd != -1))
	{
		free(g_data.env[pwd]);
		g_data.env[oldpwd] = ft_strjoin("PWD=", "");
	}
	else if ((oldpwd != -1) && (pwd != -1))
	{
		free(g_data.env[oldpwd]);
		g_data.env[oldpwd] = ft_strjoin("OLD", g_data.env[pwd]);
		free(g_data.env[pwd]);
		g_data.env[pwd] = ft_strjoin("PWD=", curdir);
	}
	free(curdir);
}

char	*addhomepath(char **strarr)
{
	char	*path;

	path = ft_strdup(my_getenv("HOME"));
	if (!path)
		return (NULL);
	if (strarr[1])
	{
		if (ft_strlen(strarr[1]) > 1)
		{
			path = ssp_strjoin(path, &strarr[1][1], 1, 0);
			if (!path)
				return (NULL);
		}
	}
	return (path);
}

// wait fix arg
int	mini_cd(char **strarr)
{
	int		oldpwd;
	int		pwd;
	char	*tohome;

	oldpwd = find_pos_env("OLDPWD");
	pwd = find_pos_env("PWD");
	if (strarr[1] == NULL)
	{
		tohome = addhomepath(strarr);
		if (chdir(tohome) == -1 || !tohome)
		{
			bltin_err_msg(my_getenv("HOME"));
			free(tohome);
			return (1);
		}
		free(tohome);
	}
	else if (chdir(strarr[1]) == -1)
	{
		bltin_err_msg(strarr[1]);
		return (1);
	}
	set_newpwdenv(oldpwd, pwd);
	return (0);
}
