NAME = fdf

SRC_DIR=srcs/

SRC = main.c\
	init.c\
	utils.c\
	get_next_line.c\
	ft_split.c\
	ft_atoi.c\
	line.c\
	rotation.c\
	utils2.c\
	parse.c\
	input.c\
	draw.c

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

CC = cc
CFLAGS = -Imlx -Iincludes -Wall -Wextra -Werror
RM = rm -f

$(NAME): $(OBJ)
	make -C ./mlx
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -lX11 -lXext -lm -o $@

all: $(NAME)

bonus: all

clean:
	$(RM) $(OBJ)

fclean: clean
	make clean -C ./mlx
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re
