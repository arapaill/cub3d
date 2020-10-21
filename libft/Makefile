# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 11:06:09 by arapaill          #+#    #+#              #
#    Updated: 2020/10/21 10:44:19 by arapaill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
	ft_tolower.c ft_strchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c\
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c\
	ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_strrchr.c

SRCSB = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c \
	ft_lstnew_bonus.c ft_lstsize_bonus.c 

CC = gcc

RM = rm -f

LIB = ar rc

CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

OBJSB = ${SRCSB:.c=.o}

NAME = libft.a

DEPS = libft.h

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 	$(NAME)

$(NAME):	${OBJS}
			${LIB} ${NAME} ${OBJS}
bonus:	${OBJSB}
			${LIB} ${NAME} ${OBJSB}


clean:
	${RM} ${OBJS} ${OBJSB}

fclean:	clean
		${RM} ${NAME}

re: fclean all

so: $(OBJS) libft.h
	    $(CC) -shared -fPIC -Wl,-soname,libft.so -o libft.so $(OBJS)
