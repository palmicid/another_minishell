/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:19:23 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 12:07:50 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "bltin_utils.h"

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
void	mini_cd(char *pathtest)
{
	int		oldpwd;
	int		pwd;
	
	oldpwd = find_pos_env("OLDPWD");
	pwd = find_pos_env("PWD");
	if ((pathtest == NULL) || (ft_strncmp(pathtest, "~", 2) == 0))
	{
		if (chdir(getenv("HOME")) == -1)
		{
			bltin_err_msg(getenv("HOME"));	
			return ;
		}
	}	
	else if (chdir(pathtest) == -1)
	{
		bltin_err_msg(pathtest);	
		return ;
	}
	set_newpwdenv(oldpwd, pwd);
	return ;
}
