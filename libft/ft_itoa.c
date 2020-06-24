/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:02:41 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 15:57:10 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*roll(int i, int neg, unsigned int nb)
{
	char			*array;

	if (neg == 1)
		i++;
	if (nb >= 2147483648 && neg == 1)
		i = 10;
	if (!(array = malloc(sizeof(char) * i + 2)))
		return (0);
	if (nb == 0)
	{
		array[0] = '0';
		array[1] = '\0';
		return (array);
	}
	array[i + 1] = '\0';
	while (nb > 0)
	{
		array[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	if (neg == 1)
		array[0] = '-';
	return (array);
}

char			*ft_itoa(int n)
{
	int				i;
	int				neg;
	unsigned int	nb;

	i = 0;
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		nb = n * -1;
	}
	else
		nb = n;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		i++;
	}
	return (roll(i, neg, nb));
}
