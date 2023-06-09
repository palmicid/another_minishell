/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:35:04 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/09 10:47:16 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLTIN_H
# define BLTIN_H

# include "minishell.h"

int		mini_echo(char **strarr);
int		mini_cd(char **strarr);
int		mini_pwd(char **strarr);
int		mini_export(char **strarr);
int		mini_unset(char **strarr);
int		mini_env(char **strarr);
int		mini_exit(char **strarr);

int		find_pos_env(char *tofind);
char	*getvarname(char *str);
char	**sp_splitndup(char **dst, char **src, int n);
int		cx_validvar(char *name);
int		free_reterr_export(char **ptr);

#endif
