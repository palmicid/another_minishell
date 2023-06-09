/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:13 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 11:43:23 by kkaiyawo         ###   ########.fr       */
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
	if (sp_digit_pm(strarr[1][i]) == 0)
		bltin_exiterr_msg(strarr[1]);
	i++;
	while (strarr[1][i])
	{
		if (ft_isdigit(strarr[1][i]) == 0)
		{
			bltin_exiterr_msg(strarr[1]);
			break ;
		}
		i++;
	}
	i = ft_atoi(strarr[1]);
	if (i > 0)
		i %= 255;
	else if (i < 0)
		i = minus_val(i);
	return (i);
}
