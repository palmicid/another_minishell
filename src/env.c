/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonegg <moonegg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 18:44:59 by moonegg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_environ(char **env)
{
	g_data.env = ft_splitdup(env);
	if (!(g_data.env))
		exit(EXIT_FAILURE);
	g_data.exit_stat = 0;
	return (0);
}

int	end_environ(void)
{
	ft_free_p2p_char(g_data.env);
	g_data.env = NULL;
	return (0);
}
