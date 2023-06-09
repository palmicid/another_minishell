/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:50:23 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 14:25:39 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strncmp(char *s1, char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n && ((*s1 == *s2) && *s1 && *s2))
// 	{
// 		i++;
// 		s1++;
// 		s2++;
// 	}
// 	if (i < n)
// 		return ((unsigned char)*s1 - (unsigned char)*s2);
// 	return (0);
// }

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (1);
	i = 0;
	while (i < n && ((s1[i] == s2[i]) && s1[i] && s2[i]))
	{
		i++;	
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}
