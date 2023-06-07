/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:37 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/02 17:07:28 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_pwd(void)
{
	char	*pathstr;

	pathstr = getcwd(NULL, 0);
	if (!pathstr)
		exit(errno);
	ft_putstr_fd(pathstr, 1);
	free(pathstr);
	// exit(EXIT_SUCCESS);
}
