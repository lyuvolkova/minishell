/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:07:03 by lubov             #+#    #+#             */
/*   Updated: 2022/04/11 23:51:18 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdupn(char *s, int n)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	count_new_words(char *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i])
		{
			i++;
			while (ft_isalnum(s[i]) && s[i])
				i++;
			words++;
		}
		else if (s[i] != '$' && s[i])
		{
			while (s[i] != '$' && s[i])
				i++;
			words++;
		}
	}
	return (words);
}

char	**new_split_process(char *s, char **str, int i, int k)
{
	int		j;

	while (s[i])
	{
		j = i;
		if (s[i] == '$' && s[i])
		{
			i++;
			while (ft_isalnum(s[i]) && s[i])
				i++;
			str[k] = ft_strdupn(&s[j], i - j);
			k++;
		}
		else if (s[i] != '$' && s[i])
		{
			while (s[i] != '$' && s[i])
				i++;
			str[k] = ft_strdupn(&s[j], i - j);
			k++;
		}
	}
	str[k] = NULL;
	return (str);
}

char	**ft_new_split(char *s)
{
	int		i;
	int		k;
	char	**str;

	i = 0;
	k = 0;
	str = malloc(sizeof (char *) * (count_new_words(s) + 1));
	if (!str)
		return (NULL);
	return (new_split_process(s, str, i, k));
}
