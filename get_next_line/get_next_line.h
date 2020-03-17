/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:39:34 by arapaill          #+#    #+#             */
/*   Updated: 2019/12/09 12:03:46 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int	    ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

#endif