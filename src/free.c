/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:54:26 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_str(t_list *lexer)
{
	t_list	*cursor;
	t_elem	*this;

	cursor = lexer->next;
	while (cursor)
	{
		this = cursor->content;
		free(this->str);
		cursor = cursor->next;
	}
}

void	free_split(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

void	free_lexer(t_list *lexer)
{
	free_str(lexer);
	ft_lstclear(&lexer, free);
}

void	free_all(t_list *lexer)
{
	free_lexer(lexer),
	free(g_global.buf);
}
