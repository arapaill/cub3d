/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 10:59:40 by arapaill          #+#    #+#             */
/*   Updated: 2020/09/07 13:12:56 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

int		get_next_line(int fd, char **line);
void	*ft_memcpy_GNL(void *dst, const void *src, size_t n);
int		ft_strlen_GNL(const char *str);
char	*ft_strjoin_GNL(char *s1, char *s2);
int		ft_strchr_GNL(const char *s, int c);
char	*ft_strdup_GNL(char *s);

#endif
