/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:21:46 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/05 14:40:23 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start_lst;
	t_list	*c_lst;
	t_list	*new;

	if (lst && f && del)
	{
		c_lst = lst;
		if (!(start_lst = ft_lstnew(f(c_lst->content))))
			return (NULL);
		while (c_lst->next)
		{
			c_lst = c_lst->next;
			if (!(new = ft_lstnew(f(c_lst->content))))
			{
				ft_lstclear(&start_lst, del);
				return (NULL);
			}
			ft_lstadd_back(&start_lst, new);
		}
		return (start_lst);
	}
	return (NULL);
}
