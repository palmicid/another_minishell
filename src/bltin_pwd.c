/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:37 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 10:58:23 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

int	mini_pwd(char **strarr)
{
	char	*pathstr;

	pathstr = getcwd(NULL, 0);
	if (!pathstr)
		exit(errno);
	ft_putstr_fd(pathstr, 1);
	free(pathstr);
	exit(EXIT_SUCCESS);
}
