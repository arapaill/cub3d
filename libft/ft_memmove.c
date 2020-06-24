/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:18:26 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 16:04:17 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	i = -1;
	if (dest == src)
		return (dest);
	else if (dest < src)
		while (++i < n)
			((unsigned char *)(dest))[i] = ((unsigned char *)(src))[i];
	else
		while (n-- > 0)
			((unsigned char *)(dest))[n] = ((unsigned char *)(src))[n];
	return (dest);
}
