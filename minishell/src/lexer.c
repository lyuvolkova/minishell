/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:27:42 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_elem	*existing_token(void)
{
	static t_elem	tokens[]
		= {
	{"<<", 2, 0, T_REDIR4, 0},
	{">>", 2, 0, T_REDIR3, 0},
	{">|", 2, 0, T_REDIR1, 0},
	{"<>", 2, 0, T_REDIR5, 0},
	{">", 1, 0, T_REDIR1, 0},
	{"<", 1, 0, T_REDIR2, 0},
	{"(", 1, 0, T_OP_PAR, 0},
	{")", 1, 0, T_CL_PAR, 0},
	{"}", 1, 0, T_CL_BRA, 0},
	{"{", 1, 0, T_OP_BRA, 0},
	{";", 1, 0, T_SEMI, 0},
	{"|", 1, 0, T_PIPE, 0},
	{"&", 1, 0, T_AND, 0},
	{" ", 1, 0, T_SPACE, 0},
	{"\\", 1, 0, T_BSLASH, 0},
	{"\n", 1, 0, T_SPACE, 0},
	{"\t", 1, 0, T_SPACE, 0},
	{NULL, 1, 0, 0, 0}
	};

	return (tokens);
}

void	add_lexer(t_list **lexer, char *input, int len, t_tokens type)
{
	char	*str;
	t_elem	*new_elem;
	t_list	*new_list;

	str = input;
	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		return ;
	new_elem->str = ft_strdup(str);
	new_elem->str[len] = 0;
	new_elem->len = len;
	new_elem->type = type;
	new_elem->this_pipe = 0;
	new_elem->quotes = 0;
	new_list = ft_lstnew(new_elem);
	ft_lstadd_back(lexer, new_list);
}

t_elem	which_token(char *input)
{
	t_elem			*ex_tok;
	t_elem			inexistant;

	ex_tok = existing_token();
	inexistant.str = NULL;
	inexistant.type = 0;
	inexistant.len = 0;
	while (ex_tok && ex_tok->str)
	{
		if (!ft_strncmp(input, ex_tok->str, ex_tok->len))
			return (*ex_tok);
		++ex_tok;
	}
	return (inexistant);
}

void	get_new_lexer(t_list *lexer)
{
	t_list	*cursor;
	t_elem	*this;
	t_elem	*next;

	cursor = lexer->next;
	while (cursor)
	{
		this = cursor->content;
		if (this->type == T_ARGS)
		{
			if (cursor->next)
			{
				next = cursor->next->content;
				while (next->type == T_ARGS && cursor->next)
				{
					next = cursor->next->content;
					this = cursor->content;
					if (next->type == T_ARGS)
						this->type = T_SPACE;
					cursor = cursor->next;
				}
			}
		}
		cursor = cursor->next;
	}
}

int	fill_lexer(char *input, t_list **lexer)
{
	t_elem	this;
	char	*last;

	last = input;
	while (*input)
	{
		this = which_token(input);
		if ((this.str || *input == '"' || *input == '\'') && last != input)
			add_lexer(lexer, last, input - last, T_ARGS);
		if (this.str)
		{
			input = input + this.len;
			add_lexer(lexer, this.str, this.len, this.type);
			last = input;
		}
		else if (!lexing_quotes(&input))
			return (0);
		else
			input++;
	}
	if (last != input)
		add_lexer(lexer, last, input - last, T_ARGS);
	return (1);
}
