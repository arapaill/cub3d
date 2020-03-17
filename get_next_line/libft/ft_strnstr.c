/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:56:31 by arapaill          #+#    #+#             */
/*   Updated: 2019/10/18 13:55:01 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char*)(&haystack[0]));
	while (i < len && haystack[i] != '\0')
	{
		k = 0;
		if (haystack[i] == needle[0])
		{
			k = i;
			while (haystack[i] == needle[j] && i < len && haystack[i] != '\0')
			{
				j++;
				i++;
				if (needle[j] == '\0')
					return ((char*)(&haystack[k]));
			}
		}
		i++;
	}
	return (0);
}
