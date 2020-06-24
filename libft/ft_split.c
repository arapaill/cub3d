/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:29:26 by arapaill          #+#    #+#             */
/*   Updated: 2019/11/11 16:22:53 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**all_free(char **array, int k)
{
	while (--k >= 0)
	{
		free(array[k]);
		array[k] = NULL;
	}
	free(array);
	array = NULL;
	return (0);
}

static int	countword(char const *s, char c)
{
	int		i;
	int		is_word;
	int		nb_word;

	i = 0;
	is_word = 0;
	nb_word = 0;
	while (s[i] != '\0')
	{
		if (is_word == 1 && s[i] == c)
			is_word = 0;
		if (is_word == 0 && s[i] != c)
		{
			nb_word++;
			is_word = 1;
		}
		i++;
	}
	return (nb_word);
}

static char	**needspace(char **array, char const *s, char c, int i)
{
	int		k;
	int		j;

	k = 0;
	j = 0;
	while (s[i] != '\0' && k < countword(s, c))
	{
		j = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			j++;
			i++;
		}
		if (!(array[k] = malloc(sizeof(char) * (j + 1))))
			return (all_free(array, k));
		ft_strlcpy(array[k++], s + i - j, j + 1);
	}
	array[k] = 0;
	return (array);
}

char		**ft_split(char const *s, char c)
{
	char	**array;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(array = malloc(sizeof(char*) * (countword(s, c) + 1))))
		return (NULL);
	return (needspace(array, s, c, i));
}
