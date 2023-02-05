/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:50:06 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_file_out(char *name)
{
	int		fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_putstr_fd("Impossible de creer le fichier", 2);
	close(fd);
}

void	redir_out(char *name, int pipe, t_list *lexer, char ***envp)
{
	int		f_stdout;
	int		fd;

	f_stdout = dup(STDOUT_FILENO);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Impossible de creer le fichier", 2);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	exec_cmd(lexer, pipe, envp);
	dup2(f_stdout, STDOUT_FILENO);
	close(fd);
}

void	create_file_appen(char *name)
{
	int		fd;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	close(fd);
}

void	redir_appen(char *name, int pipe, t_list *lexer, char ***envp)
{
	int		f_stdout;
	int		fd;

	f_stdout = dup(STDOUT_FILENO);
	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	exec_cmd(lexer, pipe, envp);
	dup2(f_stdout, STDOUT_FILENO);
	close(fd);
}
