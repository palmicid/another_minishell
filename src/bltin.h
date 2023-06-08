/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:35:04 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 14:28:35 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLTIN_H
# define BLTIN_H

# include "minishell.h"

int		find_pos_env(char *strarr);
void	bltin_err_msg(char *str);

int		mini_echo(char **strarr);
int		mini_cd(char **strarr);
int		mini_pwd(char **strarr);
int		mini_export(char **strarr);
int		mini_unset(char **strarr);
int		mini_env(char **strarr);
int		mini_exit(char **strarr);

#endif
