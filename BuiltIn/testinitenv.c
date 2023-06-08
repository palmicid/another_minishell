/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testinitenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruangde <pruangde@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 05:10:34 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/08 13:45:47 by pruangde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	**init_environ(char **temp_env)
{
	char	**tmp1;

	temp_env = ft_splitdup(environ);
	tmp1 = temp_env;
	temp_env = environ;
	environ = tmp1;
	return (temp_env);
}

char	**end_environ(char **temp_env)
{
	char	**tmp;

	tmp = temp_env;
	temp_env = environ;
	environ = tmp;
	ft_free_p2p_char(temp_env);
	temp_env = NULL;
	return (temp_env);
}

int	main(void)
{
	char	**temp = NULL;
	
	temp = init_environ(temp);
	// TEST
	// char	*str1 = getenv("PWD");
	// printf("%s\n%s\n", getenv("PWD"), getenv("OLDPWD"));
	mini_env();
	
	printf("\n\n============================================================\n\n");
	mini_unset("OLDPWD");
	printf("\n\n============================================================\n\n");
	
	mini_env();
	// printf("%s\n%s\n", getenv("PWD"), getenv("OLDPWD"));
	// TEST
	temp = end_environ(temp);
	return (0);
}
