/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:13:56 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	is_fd(t_list *lexer)
{
	t_list	*cursor;
	t_elem	*this;
	t_elem	*next;

	cursor = lexer->next;
	while (cursor->next)
	{
		this = cursor->content;
		next = cursor->next->content;
		if (this->type == T_REDIR1 || this->type == T_REDIR2
			|| this->type == T_REDIR3 || this->type == T_REDIR5)
		{
			if (next->type == T_ARGS)
				next->type = T_FD;
		}
		else if (this->type == T_REDIR4)
		{
			if (next->type == T_ARGS)
				next->type = T_DELIMITER;
		}
		cursor = cursor->next;
	}
}

void	is_cmd(t_list *lexer)
{
	t_list		*cursor;
	t_elem		*this;
	int			pipe;

	pipe = 0;
	cursor = lexer->next;
	while (cursor)
	{
		this = cursor->content;
		if (this->type == T_ARGS && pipe == 0)
		{
			this->type = T_CMD;
			pipe = 1;
		}
		if (this->type == T_PIPE)
			pipe = 0;
		cursor = cursor->next;
	}
}

void	which_pipe(t_list *lexer)
{
	t_list	*cursor;
	t_elem	*this;
	int		which;

	cursor = lexer->next;
	which = 0;
	while (cursor)
	{
		this = cursor->content;
		if (this->type == T_PIPE)
			which++;
		this->this_pipe = which;
		cursor = cursor->next;
	}
}

int	syntax_error(t_list *lexer)
{
	t_list	*last;
	t_elem	*this;

	last = ft_lstlast(lexer);
	this = last->content;
	if (this->type == T_PIPE || this->type == T_REDIR1
		|| this ->type == T_REDIR2 || this->type == T_REDIR3
		|| this->type == T_REDIR4)
	{
		ft_putstr_fd("bash : syntax error\n", 2);
		return (1);
	}
	return (0);
}
