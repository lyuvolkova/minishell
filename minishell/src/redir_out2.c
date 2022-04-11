/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:46:11 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_in_out(t_fds *fds, int pipe, t_list *lexer, char ***envp)
{
	int	f_stdin;
	int	f_stdout;
	int	fd1;
	int	fd2;

	f_stdin = dup(STDIN_FILENO);
	f_stdout = dup(STDOUT_FILENO);
	fd1 = open(fds->last_in, O_RDONLY, 0644);
	if (fd1 == -1)
	{
		printf("bash : %s : File not found.\n", fds->last_in);
		return (-1);
	}
	fd2 = open(fds->last_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	exec_cmd(lexer, pipe, envp);
	dup2(f_stdin, STDIN_FILENO);
	dup2(f_stdout, STDOUT_FILENO);
	close(fd1);
	close(fd2);
	return (0);
}

int	redir_in_appen(t_fds *fds, int pipe, t_list *lexer, char ***envp)
{
	int	f_stdin;
	int	f_stdout;
	int	fd1;
	int	fd2;

	f_stdin = dup(STDIN_FILENO);
	f_stdout = dup(STDOUT_FILENO);
	fd1 = open(fds->last_in, O_RDONLY, 0644);
	if (fd1 == -1)
	{
		printf("bash : %s : File not found.\n", fds->last_in);
		return (-1);
	}
	fd2 = open(fds->last_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	exec_cmd(lexer, pipe, envp);
	dup2(f_stdin, STDIN_FILENO);
	dup2(f_stdout, STDOUT_FILENO);
	close(fd1);
	close(fd2);
	return (0);
}

void	redir_heredoc_out(t_fds *fds, int pipe, t_list *lexer, char ***envp)
{
	int		f_stdin;
	int		f_stdout;
	int		fd1;
	int		fd2;

	f_stdin = dup(STDIN_FILENO);
	f_stdout = dup(STDOUT_FILENO);
	heredoc_while(fds->last_in);
	fd1 = open("/tmp/1", O_RDONLY, 0644);
	fd2 = open(fds->last_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	exec_cmd(lexer, pipe, envp);
	dup2(f_stdin, STDIN_FILENO);
	dup2(f_stdout, STDOUT_FILENO);
	unlink("/tmp/1");
}

void	redir_heredoc_appen(t_fds *fds, int pipe, t_list *lexer, char ***envp)
{
	int		f_stdin;
	int		f_stdout;
	int		fd1;
	int		fd2;

	f_stdin = dup(STDIN_FILENO);
	f_stdout = dup(STDOUT_FILENO);
	heredoc_while(fds->last_in);
	fd1 = open("/tmp/1", O_RDONLY, 0644);
	fd2 = open(fds->last_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	exec_cmd(lexer, pipe, envp);
	dup2(f_stdin, STDIN_FILENO);
	dup2(f_stdout, STDOUT_FILENO);
	unlink("/tmp/1");
}
