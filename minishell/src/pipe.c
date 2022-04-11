/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:39:54 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parent(int fd_in, t_list *lexer)
{
	int	i;

	i = 0;
	close(fd_in);
	while (i < (count_pipes(lexer) + 1))
	{
		wait(NULL);
		i++;
	}
}

void	close_write_read(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

void	children(t_list *lexer, int fd_in)
{
	int		i;
	int		pipes[2];
	pid_t	pid;

	i = 0;
	while (i < (count_pipes(lexer) + 1))
	{
		pipe(pipes);
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if ((i + 1) != (count_pipes(lexer) + 1))
				dup2(pipes[1], STDOUT_FILENO);
			close_write_read(pipes);
			close(fd_in);
			if (!redirection(lexer, i, &g_global.cpenv))
				exec_cmd(lexer, i, &g_global.cpenv);
			exit(0);
		}
		dup2(pipes[0], fd_in);
		close_write_read(pipes);
		i++;
	}
}

void	ft_pipex(t_list *lexer)
{
	int		fd_in;

	fd_in = dup(STDIN_FILENO);
	children(lexer, fd_in);
	parent(fd_in, lexer);
}
