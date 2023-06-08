/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:33:06 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 10:09:23 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	mini_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_putendl_fd(environ[i], STDOUT_FILENO);
		i++;
	}
}
