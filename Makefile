# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isoulima <isoulima@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/12 09:14:33 by isoulima          #+#    #+#              #
#    Updated: 2026/04/24 16:21:09 by isoulima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC		= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_DIR		= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= src/main.c \
		  src/map.c \
		  src/utils.c \
		  src/map_valid.c \
		  src/map_path.c \
		  src/render.c \
		  src/game.c \
		  src/load.c

OBJS		= $(SRCS:.c=.o)

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I include -I $(MLX_DIR) -I $(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
