/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 10:59:17 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/21 11:04:36 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strdup_gnl(char *s)
{
	char			*str;
	size_t			i;

	if (s == NULL)
		return (0);
	i = 0;
	if (!(str = malloc((sizeof(char) * (ft_strlen_gnl(s) + 1)))))
		return (0);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int			ft_strchr_gnl(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (0);
}

void		*ft_memcpy_gnl(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (!dst && !src)
		return (NULL);
	if (dst == 0)
		return (dst);
	pdst = dst;
	psrc = (unsigned char *)(src);
	i = 0;
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}

int			ft_strlen_gnl(const char *str)
{
	size_t i;

	if (str == NULL)
		return (0);
	i = 0;
	while (*str++ != '\0')
		i++;
	return (i);
}

char		*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*array;
	size_t	len1;
	size_t	len2;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup_gnl(s2));
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	if (!(array = malloc(sizeof(char ) * (len1 + len2 + 1))))
		return (NULL);
	ft_memcpy_gnl(array, s1, len1);
	ft_memcpy_gnl(&array[len1], s2, len2 + 1);
	free(s1);
	s1 = NULL;
	return (array);
}
