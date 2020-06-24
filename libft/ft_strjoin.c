/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 09:38:47 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 16:50:36 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	len1;
	size_t	len2;
	char	*array;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	if (!(array = malloc(sizeof(char ) * (len1 + len2 + 1))))
		return (NULL);
	ft_strlcpy(array, s1, len1 + 1);
	ft_strlcat(array, s2, len2 + len1 + 1);
	return (array);
}
