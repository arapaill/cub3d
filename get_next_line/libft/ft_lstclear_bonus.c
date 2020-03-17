/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:23:06 by arapaill          #+#    #+#             */
/*   Updated: 2019/10/18 12:08:42 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;

	if (lst == 0 || del == 0)
		return ;
	buffer = *lst;
	while (buffer != NULL)
	{
		*lst = buffer;
		ft_lstdelone(*lst, del);
		buffer = buffer->next;
	}
	*lst = NULL;
}
