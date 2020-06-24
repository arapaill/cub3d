/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:30:23 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 16:25:33 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		start(char const *s1, char const *set)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && ft_strrchr(set, s1[i]) != 0)
		i++;
	return (i);
}

static int		end(char const *s1, char const *set)
{
	int i;

	i = ft_strlen(s1);
	while (i > 0 && ft_strrchr(set, s1[i]) != 0)
		i--;
	return (i + 1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		j;
	char	*array;

	if (!set || !s1)
		return (NULL);
	len = ft_strlen(s1);
	i = start(s1, set);
	j = end(s1 + i, set);
	if (!(array = malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	array = ft_substr(s1, i, j);
	array[j] = '\0';
	return (array);
}
