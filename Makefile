NAME = fdf

SRC_DIR=srcs/

SRC = main.c utils.c

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

CC = cc
CFLAGS = -Imlx -Iincludes
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
