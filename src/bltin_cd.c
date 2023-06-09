/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:19:23 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 11:39:46 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

// cx arg if more than 1 stop
// --> too many arguments
// cx access dir path if no stop
// --> no such file or directory

// change environ PWD and OLDPWD
// set current PWD to OLDPWD and use getcwd to replace in PWD

static void	set_newpwdenv(int oldpwd, int pwd)
{
	char *curdir;

	curdir = getcwd(NULL, 0);
	if ((oldpwd != -1) && (pwd == -1)) // oldpwd OK pwd -1
	{
		free(environ[oldpwd]);
		environ[oldpwd] = ft_strjoin("OLDPWD=", NULL);
	}
	else if ((oldpwd == -1) && (pwd != -1)) // oldpwd -1 pwd OK
	{
		free(environ[pwd]);
		environ[oldpwd] = ft_strjoin("PWD=", NULL);
	}
	else if ((oldpwd != -1) && (pwd != -1)) // both OK
	{
		free(environ[oldpwd]);
		environ[oldpwd] = ft_strjoin("OLD", environ[pwd]);
		free(environ[pwd]);
		environ[pwd] = ft_strjoin("PWD=", curdir);
	}
	free(curdir);
}

// wait fix arg
int	mini_cd(char **strarr)
{
	int		oldpwd;
	int		pwd;

	oldpwd = find_pos_env("OLDPWD");
	pwd = find_pos_env("PWD");
	if ((strarr[1] == NULL) || (ft_strncmp(strarr[1], "~", 2) == 0))
	{
		if (chdir(getenv("HOME")) == -1)
		{
			bltin_err_msg(getenv("HOME"));
			return (1);
		}
	}
	else if (chdir(strarr[1]) == -1)
	{
		bltin_err_msg(strarr[1]);
		return (1);
	}
	set_newpwdenv(oldpwd, pwd);
	return (0);
}
