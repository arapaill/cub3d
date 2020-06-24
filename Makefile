# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/16 16:33:27 by marvin            #+#    #+#              #
#    Updated: 2020/06/24 10:14:19 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra
MFLAGS = -L lmlx -L lmlx -L lXext -L lX11 -L
SRC = ft_cub3d.c
NAME = ft_cub3D
LIB = ar rcs

all : $(NAME)

$(NAME):	
			@make -C ./libft
			@cp ./libft/libft.a libft.a
			@$(CC) $(CFLAGS) $(MFLAGS) ${SRC} libft.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled libft and GNL]"

%.o: %.c
			$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@rm -f *.o

fclean:	clean
			@rm -f $(NAME)
			@rm -f libft/libft.a
			@rm -f libft/*.o
			@rm -f a.out
re:
			fclean all

exec:	all
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out map.cub