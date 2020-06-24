/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:27:04 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 16:25:48 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(array = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		array[0] = '\0';
		return (array);
	}
	while (i < len)
	{
		array[i] = s[start];
		start++;
		i++;
	}
	array[i] = '\0';
	return (array);
}
