/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:16:43 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	new_int_error(char *cmd, char *arg, char *msg, int fd)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	if (arg)
	{
		ft_putstr_fd(arg, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (1);
}

int	cmd_error(char *cmd, char *msg, int fd)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (1);
}

int	error_bool(char *cmd, char *arg, char *msg, int fd)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	if (arg)
	{
		ft_putstr_fd(arg, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
	return (1);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
