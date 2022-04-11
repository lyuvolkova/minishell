/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 09:59:05 by lubov             #+#    #+#             */
/*   Updated: 2022/04/12 00:18:38 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parent_signal(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_global.ret = 130;
	}
}

void	child_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_global.ret = 131;
		g_global.sigquit = 1;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_global.ret = 130;
		g_global.sigint = 1;
	}
}

void	get_signal(int sig)
{
	if (g_global.pid)
		child_signal(sig);
	else
		parent_signal(sig);
}
