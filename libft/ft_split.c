/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:04:53 by lubov             #+#    #+#             */
/*   Updated: 2022/04/07 00:04:53 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_str(char const *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	**ft_strdel(char **array, int counter)
{
	int	i;

	i = 0;
	while (counter > 0)
	{
		counter--;
		free((void *)array[counter]);
		array[counter] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}

static int	count_let(const char *s, char c)
{
	int	count_letter;

	count_letter = 0;
	while (*s && *s != c)
	{
		count_letter++;
		s++;
		if (*s == '\0')
			return (count_letter);
	}
	return (count_letter);
}

static char	**check(char **array, char const *s, char c, int len)
{
	int	count_letter;
	int	m;
	int	n_str;

	n_str = 0;
	while (*s != '\0' && n_str < len)
	{
		while (*s == c)
			s++;
		count_letter = count_let(s, c);
		array[n_str] = (char *)malloc(sizeof(char) * (count_letter + 1));
		if (!array[n_str])
			return (ft_strdel(array, n_str));
		m = 0;
		while (m < count_letter)
		{
			array[n_str][m] = *s;
			m++;
			s++;
		}
		array[n_str][count_letter] = '\0';
		n_str++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		len;

	if (!s)
		return (NULL);
	len = count_str(s, c);
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	array = check(array, s, c, len);
	array[len] = 0;
	if (array)
		return (array);
	else
		return (NULL);
}
