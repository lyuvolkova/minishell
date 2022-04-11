/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:02:18 by lubov             #+#    #+#             */
/*   Updated: 2022/04/12 00:28:32 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_global;

int	too_much_ac(int ac, char **av)
{
	(void)av;
	if (ac > 1)
	{
		ft_putstr_fd("Too much arguments.\n", 2);
		return (0);
	}
	return (1);
}

void	minishell(t_list *lexer)
{
	if (lexer->next)
	{
		if (count_pipes(lexer) + 1 > 1)
			ft_pipex(lexer);
		else
		{
			if (!redirection(lexer, 0, &g_global.cpenv))
				exec_cmd(lexer, 0, &g_global.cpenv);
		}
	}	
}

int	main(int ac, char **av, char **envp)
{
	t_list		*lexer;

	if (!too_much_ac(ac, av))
		return (0);
	g_global.ret = 0;
	g_global.cpenv = copy_envp(envp);
	
	while (1)
	{
		g_global.pid = 0;
		g_global.sigint = 0;
		g_global.sigquit = 0;
		signal(SIGINT, get_signal);
		signal(SIGQUIT, get_signal);
		lexer = ft_lstnew(NULL);
		g_global.buf = readline("\033[1;33mminishell ➜ \033[m");
		if (g_global.buf == NULL)
			exit_succes(lexer);
		add_history(g_global.buf);
		if (!parsing(g_global.buf, lexer))
			g_global.ret = 127;
		else
			minishell(lexer);
		free_all(lexer);
	}
	return (g_global.ret);
}
