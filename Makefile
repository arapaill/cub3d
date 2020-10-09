# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/07 12:55:46 by arapaill          #+#    #+#              #
#    Updated: 2020/10/09 10:17:57 by arapaill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = gcc
CFLAGS = #-Wall -Wextra -Werror
MFLAGS =  -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -g -fsanitize=address
MFLAGS =  -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit
SRC = ft_cub3d.c ft_parsing.c ft_move.c ft_map_check.c ft_error_manager.c ft_sprite.c ft_parsing_sprite.c
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
			
re:			fclean all
		
exec:		all
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out map.cub
test:
			@make -C ./libft
			@cp ./libft/libft.a libft.a
			@$(CC) $(CFLAGS) $(MFLAGS) test.c libft.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
			@echo "\n\033[32m[✓]\033[0m		[TEST :compiled libft and GNL]"
			@echo "\033[32m[✓]\033[0m		[TEST and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out
