/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:03:55 by arapaill          #+#    #+#             */
/*   Updated: 2019/10/25 16:24:13 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*str;
	unsigned int	n;

	n = ft_strlen(s);
	if (!(str = malloc((sizeof(char) * (n + 1)))))
		return (0);
	ft_strlcpy(str, s, n + 1);
	str[n] = '\0';
	return (str);
}
