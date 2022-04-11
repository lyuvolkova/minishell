/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:04:28 by lubov             #+#    #+#             */
/*   Updated: 2022/04/07 00:04:28 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst1;
	unsigned char	*src1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (!dst1 && !src1)
		return (dst);
	if (dst1 > src1)
		while (len--)
			dst1[len] = src1[len];
	else
		while (len--)
			*dst1++ = *src1++;
	return (dst);
}
