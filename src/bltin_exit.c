/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:13 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 11:28:59 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltin.h"

static int	minus_val(int num)
{
	while (num < 0)
	{
		num += 256;
	}
	return (num % 256);
}

int	mini_exit(char **strarr)
{
	int	i;

	i = 0;
	if (sp_digit_pm(cmd[1][i]) == 0)
		bltin_exiterr_msg(cmd[1]);
	i++;
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1[i]]) == 0)
		{
			bltin_exiterr_msg(cmd[1]);
			break ;
		}
		i++;
	}
	i = ft_atoi(cmd[1]);
	if (i > 0)
		i %= 255;
	else if (i < 0)
		i = minus_val(i);
	return (i);
}
