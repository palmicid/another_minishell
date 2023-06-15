/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:20:13 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 16:37:29 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minus_val(long num)
{
	while (num < 0)
		num += 256;
	return (num);
}

static int	exit_with_err(char *str)
{
	bltin_exiterr_msg(str);
	return (2);
}

static int	cx_19aft(char *str)
{
	int	i;
	int	c;

	i = 0;
	while (str[i])
	{
		c = 0;
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (ft_isdigit(str[i]))
		{
			c++;
			i++;
		}
		if (c > 19 || c == 0)
			return (1);
		if (str[i] != 0)
			return (1);
	}
	return (0);
}

// -1 on not OK, >= 0 if OK
static int	convert_code(char *str, long *code)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	tmp = 0;
	sign = cx_signfirstpos(str, &i);
	while (str[i])
	{
		tmp *= 10;
		tmp += str[i++] - '0';
	}
	tmp *= sign;
	if (sign == -1 && (tmp > 0))
		return (1);
	else if ((sign == 1) && (tmp < 0))
		return (1);
	if (tmp > LONG_MAX)
		return (1);
	if (sign == -1)
		*code = minus_val(tmp);
	else
		*code = tmp % 256;
	return (0);
}

int	mini_exit(char **strarr)
{
	long	code;

	ft_putendl_fd("exit", 1);
	if (!strarr[1])
		return (EXIT_SUCCESS);
	if (sp_digit_pm_str(strarr[1]))
		return (exit_with_err(strarr[1]));
	if (cx_19aft(strarr[1]))
		return (exit_with_err(strarr[1]));
	if (convert_code(strarr[1], &code))
		return (exit_with_err(strarr[1]));
	return ((int)code);
}
