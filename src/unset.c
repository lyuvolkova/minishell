/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:32:11 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_envkey(char *key, char **envp)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], key_len) == 0
			&& (envp[i][key_len] == '=' || envp[i][key_len] == 0))
			return (i);
		i++;
	}
	return (-1);
}

void	delete_env(int idx, char **envp)
{
	free(envp[idx]);
	while (envp[idx])
	{
		envp[idx] = envp[idx + 1];
		idx++;
	}
}

int	ft_unset(t_list *lexer, int pipe, char **envp)
{
	t_list	*cursor;
	t_elem	*this;
	int		idx;

	cursor = while_pipe(pipe, lexer);
	this = cursor->content;
	while (this->this_pipe == pipe && cursor)
	{
		this = cursor->content;
		if (this->type == T_ARGS)
		{
			if (is_valid_key(this->str))
			{
				idx = ft_find_envkey(this->str, envp);
				if (idx > -1)
					delete_env(idx, envp);
			}
			else
				new_int_error("unset", this->str, "not valid a identifier", 2);
		}
		cursor = cursor->next;
	}
	return (1);
}
