/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:33:06 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 09:50:19 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

int	mini_env(char **strarr)
{
	int	i;

	(void) strarr;
	i = 0;
	while (environ[i])
	{
		ft_putendl_fd(environ[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
