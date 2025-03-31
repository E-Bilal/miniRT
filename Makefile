# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 18:38:18 by bel-bouc          #+#    #+#              #
#    Updated: 2024/11/25 13:11:02 by senayat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

FLAGS = -Wextra -Wall -Werror

SRC_LIBFT           := libft/ft_split.c libft/ft_strlen.c libft/ft_strncmp.c
SRC_PARSER          := parser/ft_convert_to_number.c parser/ft_file_util.c parser/ft_parse_ambient_light.c parser/ft_parse_camera.c parser/ft_parse_cylinder.c parser/ft_parse_light.c parser/ft_parse_plane.c parser/ft_parse_sphere.c parser/ft_parsecolors.c parser/ft_parsecoordinates.c parser/ft_parsermain.c parser/ft_parsevectors.c

SRC_UTIL           := util/ft_debug.c util/ft_hooks.c util/ft_init_structs_data.c util/ft_mlx.c

SRC_MENU           := menu/color_menu.c menu/crd_menu.c menu/decrement_util.c menu/edit_menu.c menu/ft_mainmenu.c menu/increment_util.c menu/vec_menu.c

SRC_MATH           := math/ft_math_util.c math/ft_quaternion.c math/ft_vec_crd_arithmetic.c math/ft_vector_arithmetic.c

SRC_RAYTRACING     := raytracing/ft_camera.c raytracing/ft_color.c raytracing/ft_create_ray.c raytracing/ft_create_viewport.c raytracing/ft_ray_cylinder.c raytracing/ft_ray_plane.c raytracing/ft_ray_sphere.c raytracing/ft_raymain.c raytracing/ft_shadow.c raytracing/ft_shadow_help.c

SRC_GET_NEXT_LINE  := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRC_MAIN           := main.c

OBJ_LIBFT           := $(patsubst libft/%, obj/%,\
                     $(patsubst %.c, %.o,\
                       $(patsubst %.c, %.o, $(SRC_LIBFT))))

OBJ_PARSER           := $(patsubst parser/%, obj/%,\
                     $(patsubst %.c, %.o,\
                       $(patsubst %.c, %.o, $(SRC_PARSER))))

OBJ_UTIL           := $(patsubst util/%, obj/%,\
                     $(patsubst %.c, %.o,\
                       $(patsubst %.c, %.o, $(SRC_UTIL))))

OBJ_MENU           := $(patsubst menu/%, obj/%,\
                     $(patsubst %.c, %.o,\
                       $(patsubst %.c, %.o, $(SRC_MENU))))
OBJ_MATH           := $(patsubst math/%, obj/%,\
                     $(patsubst %.c, %.o,\
                       $(patsubst %.c, %.o, $(SRC_MATH))))

OBJ_RAYTRACING           := $(patsubst raytracing/%, obj/%,\
                     $(patsubst %.c, %.o,\
                       $(patsubst %.c, %.o, $(SRC_RAYTRACING))))

OBJ_GET_NEXT_LINE           := $(patsubst get_next_line/%, obj/%,\
                     $(patsubst %.c, %.o,\
                       $(patsubst %.c, %.o, $(SRC_GET_NEXT_LINE))))

OBJ_MAIN        := obj/main.o

MLX_LINUXA = mlx_linux/libmlx_Linux.a


$(NAME): $(OBJ_MAIN) $(OBJ_LIBFT) $(OBJ_GET_NEXT_LINE) $(OBJ_UTIL) $(OBJ_PARSER) $(OBJ_MENU) $(OBJ_MATH) $(OBJ_RAYTRACING) $(MLX_LINUXA)
	gcc  -o $@ $^ -lXext -lX11 -lm 
	
$(MLX_LINUXA): mlx_linux/Makefile
	cd mlx_linux && make 		

obj/%.o: **/%.c
	gcc $(FLAGS) -lXext -lX11 -lm -g -o $@ -c $< 

$(OBJ_MAIN) : $(SRC_MAIN)
	gcc $(FLAGS) -c  $(SRC_MAIN) -g -o obj/main.o 

all: $(NAME)

clean:
	rm -f $(OBJ_GET_NEXT_LINE) $(OBJ_LIBFT) $(OBJ_UTIL) $(OBJ_PARSER) $(OBJ_MENU) $(OBJ_MATH) $(OBJ_RAYTRACING) $(OBJ_MAIN)

fclean:
	rm -f $(OBJ_GET_NEXT_LINE) $(OBJ_LIBFT) $(OBJ_UTIL) $(OBJ_PARSER) $(OBJ_MENU) $(OBJ_MATH) $(OBJ_RAYTRACING) $(OBJ_MAIN) $(NAME)

re: fclean all

.PHONY : all clean fclean re 
