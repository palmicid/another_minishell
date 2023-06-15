/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:37 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 16:37:30 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(char **strarr)
{
	char	*pathstr;

	(void) strarr;
	pathstr = getcwd(NULL, 0);
	if (!pathstr)
		return (errno);
	ft_putendl_fd(pathstr, 1);
	free(pathstr);
	return (0);
}
