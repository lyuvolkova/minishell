/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:11:17 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_too_much_args(t_elem *this)
{
	if (this->type == T_ARGS)
	{
		cmd_error("pwd", "too many aguments", 2);
		return (0);
	}
	return (1);
}

int	ft_pwd(t_list *lexer, int pipe)
{
	t_list	*cursor;
	t_elem	*this;
	char	*path;

	cursor = while_pipe(pipe, lexer);
	this = cursor->content;
	path = getcwd(NULL, 0);
	while (this->this_pipe == pipe && cursor)
	{
		this = cursor->content;
		if (!pwd_too_much_args(this))
			return (0);
		if (!path)
		{
			return (new_int_error("pwd", "getcwd", strerror(errno), 2));
		}
		cursor = cursor->next;
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	return (0);
}
