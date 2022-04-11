/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ut2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:57:51 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_global.cpenv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_str_swith(g_global.cpenv[i], tmp))
		{
			free(tmp);
			return (ft_strchr(g_global.cpenv[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

int	print_error(char *path)
{
	DIR	*dir;
	int	fd;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putstr_fd(" command not found\n", STDERR);
	else if (fd != -1 && dir == NULL)
		ft_putstr_fd(" permission denied\n", STDERR);
	else if (fd == -1 && dir != NULL)
		ft_putstr_fd(" is a directory\n", STDERR);
	else if (fd == -1 && dir == NULL)
		ft_putstr_fd(" no such file or directory\n", STDERR);
	if (path == NULL && fd == -1 && dir == NULL)
		g_global.ret = 127;
	else
		g_global.ret = 127;
	if (dir)
		closedir(dir);
	close (fd);
	return (g_global.ret);
}

int	ft_process(char *path, char **args)
{
	g_global.ret = 0;
	g_global.pid = fork();
	if (g_global.pid == 0)
	{
		if (ft_strchr(path, '/') != NULL)
			g_global.ret = execve(path, args, g_global.cpenv);
		g_global.ret = print_error(path);
		exit(g_global.ret);
	}
	else
		waitpid(g_global.pid, &g_global.ret, 0);
	if (g_global.sigint == 1 || g_global.sigquit == 1)
		return (g_global.ret);
	if (g_global.ret == 32512 || g_global.ret == 32256)
		return (g_global.ret = g_global.ret / 256);
	else
		return (!!g_global.ret);
	return (g_global.ret);
}

char	*check_bin(char *bin, char *cmd)
{
	DIR				*dir;
	struct dirent	*repo;
	char			*path;

	path = NULL;
	dir = opendir(bin);
	if (!dir)
		return (NULL);
	while (1)
	{
		repo = readdir(dir);
		if (!repo)
			break ;
		if (ft_strcmp(repo->d_name, cmd) == 0)
			path = strjoin_path(bin, repo->d_name);
	}
	closedir(dir);
	return (path);
}
