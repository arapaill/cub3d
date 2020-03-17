/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:21:34 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/08 15:24:00 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	if (b == NULL)
		return (NULL);
	ptr = (unsigned char*)b;
	while (len-- > 0)
		*ptr++ = (unsigned char)c;
	return (b);
}
