/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:37 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 14:16:20 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"
#include "minishell.h"

int	mini_pwd(char **strarr)
{
	char	*pathstr;

	pathstr = getcwd(NULL, 0);
	if (!pathstr)
		exit(errno);
	ft_putstr_fd(pathstr, 1);
	free(pathstr);
	// exit(EXIT_SUCCESS);
}
