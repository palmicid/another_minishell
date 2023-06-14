/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/14 15:03:13 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_environ(t_data *data)
{
	char	**tmp1;

	tmp1 = ft_splitdup(environ);
	if (!(tmp1))
		exit(EXIT_FAILURE);
	data->env = environ;
	environ = tmp1;
	data->exit_stat = 0;
	return (0);
}

int	end_environ(t_data *data)
{
	char	**tmp;

	tmp = data->env;
	data->env = environ;
	environ = tmp;
	ft_free_p2p_char(data->env);
	data->env = NULL;
	return (0);
}
