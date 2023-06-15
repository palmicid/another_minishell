/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonegg <moonegg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:18:56 by pruangde          #+#    #+#             */
/*   Updated: 2023/06/15 18:42:32 by moonegg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int	soloexecve(t_listcmd *cmdlist, t_data *data)
{
	if (cmdlist->next == NULL)
	{
		if (ft_strncmp(cmdlist->cmd[0], "exit", 5) == 0)
			data->exit_stat = mini_exit(cmdlist->cmd);
		else if (ft_strncmp(cmdlist->cmd[0], "export", 7) == 0)
			data->exit_stat = mini_export(cmdlist->cmd) % 256;
		else if (ft_strncmp(cmdlist->cmd[0], "unset", 6) == 0)
			data->exit_stat = mini_unset(cmdlist->cmd) % 256;
		else if (ft_strncmp(cmdlist->cmd[0], "cd", 3) == 0)
			data->exit_stat = mini_cd(cmdlist->cmd) % 256;
		else
			data->exit_stat = executor(cmdlist, g_data.env) % 256;
	}
	else
		data->exit_stat = executor(cmdlist, g_data.env) % 256;
	if (cmdlist->next == NULL && ft_strncmp(cmdlist->cmd[0], "exit", 5) == 0)
	{
		return (1);
	}
	return (0);
}

int	ismulticmd(char *strcmd)
{
	int	i;

	i = 0;
	while (strcmd[i])
	{
		if (strcmd[i] == '|')
			return (1);
		if (strcmd[i] == 34 || strcmd[i] == 39)
			i = find_pair(strcmd, i);
		i++;
	}
	return (0);
}

static void	exit_end(char **strcmd)
{
	int	n;

	n = g_data.exit_stat;
	free(strcmd[0]);
	end_environ();
	exit(n);
}

// the child going to be parent for all program
int	process(char *strcmd)
{
	int			stat;
	t_listcmd	*cmdlist;

	cmdlist = NULL;
	add_history(strcmd);
	cmdlist = str_split(strcmd);
	if (cmdlist == NULL)
		return (0);
	stat = soloexecve(cmdlist, &g_data);
	cmdlist = free_cmdlist(cmdlist);
	return (stat);
}

int	main(int ac, char **av, char **env)
{
	char	*strcmd;
	int		x;

	(void) av;
	g_data.exit_stat = ac - ac;
	strcmd = NULL;
	init_environ(env);
	signal_handling();
	while (1)
	{
		signal_int_handling(1);
		strcmd = readline("minishell-1.0$ ");
		if (!strcmd)
			break ;
		else if (strcmd[0] == '\0')
			;
		else if (ft_strlen(strcmd) > 0)
			x = process(strcmd);
		if (x == 1)
			exit_end(&strcmd);
		free(strcmd);
	}
	ft_putendl_fd("exit", 1);
	exit(end_environ());
}
