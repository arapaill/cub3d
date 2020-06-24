/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:41:54 by arapaill          #+#    #+#             */
/*   Updated: 2020/06/24 10:13:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

static int		ispace(const char *str, int *j)
{
	int						i;
	int						neg;

	i = 0;
	neg = 0;
	while (str[i] == '\0' ||
			str[i] == '\t' ||
			str[i] == '\n' ||
			str[i] == '\v' ||
			str[i] == '\f' ||
			str[i] == '\r' ||
			str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	*j = i;
	return (neg);
}

int				ft_atoi(const char *str)
{
	int			i;
	int			neg;
	__uintmax_t	n;
	__uintmax_t	min;

	min = 9223372036854775807;
	n = 0;
	i = 0;
	neg = ispace(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n + (str[i] - '0');
		n = n * 10;
		i++;
		if (n >= (min + 1) && neg == 1)
			return (0);
		else if (n >= 9223372036854775807 && neg == 0)
			return (-1);
	}
	n = n / 10;
	if (neg == 1)
		return ((int)n * (-1));
	else
		return ((int)n);
}
