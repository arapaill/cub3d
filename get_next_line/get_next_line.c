/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 11:00:02 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/21 11:05:29 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*cut(char *str, size_t size)
{
	char		*array;

	array = ft_strdup_gnl(str);
	free(str);
	if (!(str = malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_memcpy_gnl(str, array, size + 1);
	str[size] = '\0';
	free(array);
	array = NULL;
	return (str);
}

int			if_rest(char **rest, char **line)
{
	if (ft_strchr_gnl(*line, '\n') != 0)
	{
		*rest = ft_strdup_gnl(&(*line)[ft_strchr_gnl(*line, '\n') + 1]);
		*line = cut(*line, ft_strchr_gnl(*line, '\n'));
		return (1);
	}
	return (0);
}

int			last_line(char **line, int ret, char **rest)
{
	free(*rest);
	*rest = NULL;
	if (ft_strlen_gnl(*line) == 0 && ret == 0)
	{
		free(*line);
		if (!(*line = malloc(sizeof(char) * 1)))
			return (-1);
		*line[0] = '\0';
	}
	return (0);
}

int			read_line(int fd, char **line, char **rest, char *buf)
{
	int			ret;

	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((*line = ft_strjoin_gnl(*line, buf)) == 0)
			return (-1);
		if (*line[0] == '\n')
		{
			*rest = ft_strdup_gnl(&(*line)[1]);
			*line = cut(*line, ft_strchr_gnl(*line, 1));
			return (1);
		}
		if (ft_strchr_gnl(*line, '\n') != 0)
		{
			*rest = ft_strdup_gnl(&(*line)[ft_strchr_gnl(*line, '\n') + 1]);
			*line = cut(*line, ft_strchr_gnl(*line, '\n'));
			return (1);
		}
	}
	return (last_line(line, ret, rest));
}

int			get_next_line(int fd, char **line)
{
	static char	*rest;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd > OPEN_MAX || line == NULL ||
	BUFFER_SIZE <= 0 || read(fd, buf, 0))
		return (-1);
	*line = ft_strdup_gnl(0);
	if (rest != NULL)
	{
		free(*line);
		*line = ft_strdup_gnl(rest);
		free(rest);
		rest = NULL;
		if (*line[0] == '\n')
		{
			rest = ft_strdup_gnl(&(*line)[1]);
			*line = cut(*line, ft_strchr_gnl(*line, 1));
			return (1);
		}
		if (if_rest(&rest, line) == 1)
			return (1);
	}
	return (read_line(fd, line, &rest, buf));
}
