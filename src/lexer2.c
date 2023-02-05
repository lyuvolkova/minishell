/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:15:47 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_lexer(t_list *lexer)
{
	t_list	*cursor;
	t_elem	*this;

	cursor = lexer->next;
	while (cursor)
	{
		this = cursor->content;
		printf("[str : %s ;\ttype = %i;\tquotes = %d\tpipe = %d]\n",
			this->str, this->type, this->quotes, this->this_pipe);
		cursor = cursor->next;
	}
	printf("\n");
}

int	lexing_squote(char **input)
{
	char	*str;

	str = *input;
	if (*str == '\'')
	{
		str++;
		while (*str && *str != '\'')
			str++;
		if (!*str || *str != '\'')
			return (0);
	}
	*input = str;
	return (1);
}

int	lexing_dquote(char **input)
{
	char	*str;

	str = *input;
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		if (!*str || *str != '"')
			return (0);
	}
	*input = str;
	return (1);
}

int	lexing_quotes(char **input)
{
	if (**input == '"' || **input == '\'')
	{
		if (!lexing_squote(input))
			return (0);
		else if (!lexing_dquote(input))
			return (0);
		input++;
	}
	return (1);
}
