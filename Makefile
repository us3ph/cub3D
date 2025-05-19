NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

RM = rm -rf

MLX_FLAGS = -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz

MLX_INCLUDE = -Iminilibx-linux

SRC = ft_split.c get_next_line.c get_next_line_utils.c read_map.c main.c utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)


%.o: %.c cub3D.h
	$(CC) $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re

.SECONDARY: