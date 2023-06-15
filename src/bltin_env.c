/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:33:06 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 17:23:37 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(char **strarr)
{
	int	i;

	(void) strarr;
	i = 0;
	while (g_data.env[i])
	{
		ft_putendl_fd(g_data.env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
