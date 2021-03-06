# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/07 12:55:46 by arapaill          #+#    #+#              #
#    Updated: 2020/10/29 11:17:35 by arapaill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
MFLAGS =  -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror
MFLAGS =  -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit
SRC = 	src/ft_cub3d.c src/ft_check_name.c src/ft_parsing.c src/ft_parsing_id.c src/ft_pars_map.c \
		src/ft_move.c src/ft_map_check.c src/ft_error_manager.c src/ft_sprite.c src/ft_parsing_sprite.c \
		src/ft_save.c src/ft_raycasting.c src/ft_raycasting_nxt.c src/ft_floor_ceiling.c src/ft_rotation.c \
		src/ft_sprite_nxt.c src/ft_map_separete.c src/ft_init_data.c 
NAME = cub3d
LIB = ar rcs

all : $(NAME)

$(NAME):	
			@make -C ./libft
			@cp ./libft/libft.a libft.a
			@$(CC) $(CFLAGS) $(MFLAGS) -o $(NAME) ${SRC} libft.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled libft and GNL]"

%.o: %.c
			$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@rm -f *.o

fclean:	clean
			@rm -f $(NAME)
			@rm -f libft/libft.a
			@rm -f libft.a
			@rm -f libft/*.o
			@rm -f a.aout
			@rm -f capture.bmp
			
re:			fclean all
		
exec:		re
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME) map.cub

save:		all
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME) map.cub --save
			@open capture.bmp
norm:
			norminette $(SRC) ft_cub3d.h keynote.h