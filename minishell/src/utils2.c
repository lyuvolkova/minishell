/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:01:49 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*while_pipe(int pipe, t_list *lexer)
{
	t_elem	*this;
	t_list	*cursor;

	cursor = lexer->next;
	this = cursor->content;
	while (this->this_pipe != pipe)
	{
		this = cursor->content;
		cursor = cursor->next;
	}
	return (cursor);
}

void	which_quotes(t_list *lexer)
{
	t_list	*cursor;
	t_elem	*this;

	cursor = lexer->next;
	while (cursor)
	{
		this = cursor->content;
		if (this->str[0] == '\'')
			this->quotes = 2;
		else if (this->str[0] == '"')
			this->quotes = 1;
		cursor = cursor->next;
	}
}

int	has_error(t_elem *this, t_elem *next)
{
	if (this->type == T_REDIR1 || this->type == T_REDIR2
		|| this->type == T_REDIR3
		|| this->type == T_REDIR4 || this->type == T_REDIR5)
	{
		if (next->type != T_FD && next->type != T_DELIMITER)
		{
			ft_putstr_fd("bash : syntax error\n", 2);
			return (0);
		}
	}
	if (this->type == T_PIPE)
	{
		if (next->type == T_PIPE)
		{
			ft_putstr_fd("bash : syntax error\n", 2);
			return (0);
		}
	}
	return (1);
}

int	check_error(t_list *lexer)
{
	t_list		*cursor;
	t_elem		*this;
	t_elem		*next;

	cursor = lexer->next;
	this = cursor->content;
	if (ft_lstsize(lexer) == 2)
	{
		if (this->type != T_CMD)
		{
			ft_putstr_fd("bash : syntax error\n", 2);
			return (0);
		}
	}
	while (cursor->next)
	{
		this = cursor->content;
		next = cursor->next->content;
		if (!has_error(this, next))
			return (0);
		cursor = cursor->next;
	}
	return (1);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*last;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = ft_lstlast(*alst);
	last->next = new;
	new->previous = last;
}
