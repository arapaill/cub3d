/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:12:38 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 16:20:22 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*buffer;

	if (lst == NULL || f == NULL)
		return ;
	buffer = lst;
	while (buffer != NULL)
	{
		lst = buffer;
		f(lst->content);
		buffer = buffer->next;
	}
}
