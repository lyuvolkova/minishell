/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:03:14 by lubov             #+#    #+#             */
/*   Updated: 2022/04/07 00:03:14 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	minus;
	int	result;
	int	i;

	minus = 1;
	result = 0;
	i = 0;
	while (str[i] && ((str[i] == 32 || (str[i] > 8 && str[i] < 14))))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -minus;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (result > 214748364 && str[i] - '0' >= 7)
			return (-1);
		if (result < -214748364 && str[i] - '0' >= 8)
			return (0);
		result = result * 10 + minus * (str[i] - '0');
		i++;
	}
	return (result);
}
