/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:56:31 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 16:25:02 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	lenneedle;

	lenneedle = ft_strlen(needle);
	i = 0;
	if (!*needle)
		return ((char*)haystack);
	while (len >= lenneedle && haystack[i])
	{
		if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
			return ((char*)haystack + i);
		i++;
		len--;
	}
	return (NULL);
}
