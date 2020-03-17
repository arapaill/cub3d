/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:39:32 by arapaill          #+#    #+#             */
/*   Updated: 2019/12/10 12:10:01 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*cut(char *str, size_t size)
{
	char *array;

	array = ft_strdup(str);
	if (!(str = malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_memcpy(str, array, size + 1);
	str[size] = '\0';
	free(array);
	array = NULL;
	return (str);
}

int			if_rest(char **rest, char **line)
{
	//printf("\nif_rest 1 %s \n\n", *rest);
	if (ft_strchr(*line, '\n') != 0)
	{
		*line = cut(*line, ft_strchr(*line, '\n'));
		//printf("\nRETEST %s \n\n", &(*rest)[2]);
		*rest = ft_strdup(&(*rest)[ft_strchr(*rest, '\n') + 1]);
		//printf("\nif_rest 2 %s\n\n", *rest);
		//sleep(1);
		//free(temp);
		return (1);
	}
	return(0);
}

int		last_line(char **line, int ret, char **rest)
{
	if (ft_strlen(*line) == 0 && ret == 0)
	{
		if (!(*line = malloc(sizeof(char) * 1)))
			return (-1);
		*line[0] = '\0';
	}
	if(ft_strlen(*rest) != 0)
	{
		//printf("\nREST : %s\n", *rest);
		free(*rest);
		rest = NULL;
		//printf("REST1 : %p\n", rest);
	}
	return (0);
}

int		read_line(int fd, char **line, char **rest, char *buf)
{
	int			ret;

	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		//printf("ret : %i\n", ret);
		buf[ret] = '\0';
		//printf("line read: %s \n", *line);
		if ((*line = ft_strjoin(*line, buf)) == 0) 
			return (-1);
			//printf("after join: %s \n", *line);
		if (*line[0] == '\n')
		{
			//printf("test: %s \n", *line);
			*line = cut(*line, ft_strchr(*line, 1));
			*rest = ft_strdup(&buf[1]);
			return (1);
		}
		//printf("dans le if %d \n", ft_strchr(*line, '\n' ));
		if (ft_strchr(*line, '\n') != 0)
		{
			*rest = ft_strdup(&buf[ft_strchr(buf, '\n') + 1]);
			//printf("befor a cut: %s\n",*line);
			*line = cut(*line, ft_strchr(*line, '\n'));
			//printf("after a cut: %s\n",*line);
			return (1);
		}
	}
	return (last_line(line, ret, rest));
}

int		get_next_line(int fd, char **line)
{
	static char	*rest = NULL;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd > FOPEN_MAX || line == NULL || BUFFER_SIZE <= 0 || read(fd, buf, 0))
		return (-1);
	if (rest != NULL)
	{
		//printf("REST 0 : %p\n", rest);
		*line = ft_strdup(rest);
		if (*line[0] == '\n')
		{
			*line = cut(*line, ft_strchr(*line, 1));
			rest = ft_strdup(&rest[1]);
			return (1);
		}
		if (if_rest(&rest, line) == 1)
		{
			//printf(" rest2 : %s\n", rest);
			return (1);
		}
	}
	return (read_line(fd, line, &rest, buf));
}
/*
int main()
{
	int fd;
	char **line;
	int i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (get_next_line(fd, line))
	{
		printf(" main [%i] : %s \n",i, *line);
		free(*line);
		i++;
	}
	printf(" main [%i] : %s \n",i, *line);
	//system("leaks a.out");
	return (0);
}
*/