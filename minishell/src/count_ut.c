/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:38:58 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_list *lexer, int pipe)
{
	int		args;
	t_list	*cursor;
	t_elem	*this;

	cursor = while_pipe(pipe, lexer);
	this = cursor->content;
	args = 0;
	while (cursor && this->this_pipe == pipe)
	{
		this = cursor->content;
		if (this->type == T_ARGS)
			args++;
		cursor = cursor->next;
	}
	return (args);
}

int	check_args(t_list *lexer, int pipe)
{
	if (count_args(lexer, pipe) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments.\n", 2);
		return (1);
	}
	return (0);
}

int	count_pipes(t_list *lexer)
{
	t_list	*cursor;
	t_elem	*this;
	int		nb;

	cursor = lexer->next;
	nb = 0;
	while (cursor)
	{
		this = cursor->content;
		if (this->type == T_PIPE)
			nb++;
		cursor = cursor->next;
	}
	return (nb);
}
