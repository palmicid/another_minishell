/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_errmsg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:01:54 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 09:14:05 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	bltin_err_msg(char *str)
{
	char	*strerr;

	strerr = strerror(errno);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("MNsh: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerr, 2);
}
