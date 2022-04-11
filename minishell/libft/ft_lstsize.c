/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:18:19 by lubov             #+#    #+#             */
/*   Updated: 2022/04/07 00:07:17 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int			len;
	t_list		*list;

	len = 0;
	list = lst;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}
