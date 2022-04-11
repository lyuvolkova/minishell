/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:28:37 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_str_a_nbr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_succes(t_list *lexer)
{
	free_str(lexer);
	ft_lstclear(&lexer, free);
	clear_history();
	free(g_global.buf);
	printf("exit\n");
	exit(g_global.ret);
}

int	exit_too_much_args(t_elem *this, int nbr_args)
{
	if (this->type == T_ARGS)
	{
		if (nbr_args == 1)
		{
			printf("bash: exit: too much arguments.\n");
			return (-1);
		}
	}
	return (0);
}

int	make_exit(t_elem *this, t_list *cursor, int nbr_args)
{
	if (this->type == T_ARGS)
	{
		if (is_str_a_nbr(this->str) && g_global.ret == 0)
		{
			g_global.ret = ft_atoi(this->str);
			nbr_args++;
		}
		else if (!is_str_a_nbr(this->str))
		{
			printf("bash: %s: numeric argument requested.\n", this->str);
			return (2);
		}
		if (cursor->next)
		{
			cursor = cursor->next;
			if (exit_too_much_args(this, nbr_args) == -1)
				return (-1);
		}
	}
	return (g_global.ret);
}

int	ft_exit(t_list *lexer, int pipe)
{
	t_list	*cursor;
	t_elem	*this;
	int		ret;
	int		nbr_args;

	cursor = lexer->next;
	this = cursor->content;
	ret = 0;
	nbr_args = 0;
	while (this->this_pipe != pipe)
	{
		this = cursor->content;
		cursor = cursor->next;
	}
	while (this->this_pipe == pipe && cursor)
	{
		this = cursor->content;
		ret = make_exit(this, cursor, nbr_args);
		if (ret == 2)
			return (2);
		else if (ret == -1)
			return (-1);
		cursor = cursor->next;
	}
	return (ret);
}
