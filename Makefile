# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:35:48 by seseo             #+#    #+#              #
#    Updated: 2022/05/12 17:11:44 by seseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR 		:=	src
OBJ_DIR			:=	obj

SRC				:=	$(SRC_DIR)/fdf_main.c \
					$(SRC_DIR)/fdf_map_parsing_1.c \
					$(SRC_DIR)/fdf_map_parsing_2.c \
					$(SRC_DIR)/fdf_map_parsing_3.c \
					$(SRC_DIR)/fdf_math_1.c \
					$(SRC_DIR)/fdf_math_2.c \
					$(SRC_DIR)/fdf_key_hook.c \
					$(SRC_DIR)/fdf_mlx_loop.c \
					$(SRC_DIR)/fdf_draw_line.c \
					$(SRC_DIR)/fdf_utils.c \
					$(SRC_DIR)/fdf_projection_utils.c

OBJ				:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME			:=	fdf
CC				:=	gcc
RM				:=	rm -rf
CFLAGS			:=	-Wall -Wextra -Werror -Iinclude -Imlx
LIB_PATH		:=	libft
MLX_PATH		:=	mlx
MLX_LIB			:=	libmlx.dylib

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJ)
					@$(MAKE) -C $(MLX_PATH)
					@$(MAKE) BONUS=true -C $(LIB_PATH)
					$(CC) $(OBJ) -Lmlx -Llibft -lmlx -lft -framework OpenGL -framework AppKit -o $(NAME)

all:				$(NAME)

clean:
					$(RM) $(OBJ)
					@$(MAKE) -C $(MLX_PATH) clean
					@$(MAKE) -C $(LIB_PATH) clean

fclean:				clean
					@$(MAKE) -C $(LIB_PATH) fclean
					$(RM) $(MLX_LIB)
					$(RM) $(NAME)

re:					fclean
					@$(MAKE) all

.PHONY:				all clean fclean re
