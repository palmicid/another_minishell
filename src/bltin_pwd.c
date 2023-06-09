/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:37 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 11:43:33 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

int	mini_pwd(char **strarr)
{
	char	*pathstr;

	(void) strarr;
	pathstr = getcwd(NULL, 0);
	if (!pathstr)
		return (errno);
	ft_putstr_fd(pathstr, 1);
	free(pathstr);
	return (0);
}
