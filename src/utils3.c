/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:10:21 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_vec(t_vec *cpt)
{
	cpt->i = 0;
	cpt->j = 0;
	cpt->k = 0;
}

char	*rejoin_the_split(char **s)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = ft_strdup("");
	while (s[i])
	{
		tmp = ft_strjoin(str, s[i]);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	return (str);
}
