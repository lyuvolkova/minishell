/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:03:56 by lubov             #+#    #+#             */
/*   Updated: 2022/04/07 00:03:56 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	memory(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len = 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*result(char *str, int len, int n)
{
	int	i;

	i = 1;
	while (n != 0)
	{
		str[len - i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == -0)
		return (ft_strdup("0"));
	len = memory(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	return (result(str, len, n));
}
