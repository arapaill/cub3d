/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:21:04 by arapaill          #+#    #+#             */
/*   Updated: 2019/10/22 09:41:44 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = (int)ft_strlen(s) + 1;
	while (--i >= 0)
		if (s[i] == c)
			return (char*)(&s[i]);
	if (s[i] == '\0' && c == '\0')
		return (char*)(&s[i]);
	return (0);
}
