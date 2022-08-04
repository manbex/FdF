NAME = fdf

SRC_DIR=srcs/

SRC = main.c init.c utils.c get_next_line.c get_next_line_utils.c ft_split.c ft_atoi.c
TEST = test.c

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))
TEST_OBJ = $(addprefix testy/, $(TEST:.c=.o))

CC = cc
CFLAGS = -Imlx -Iincludes
RM = rm -f

$(NAME): $(OBJ)
	make -C ./mlx
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -lX11 -lXext -lm -o $@

all: $(NAME)

bonus: all

test: $(TEST_OBJ)
	make -C ./mlx
	$(CC) $(CFLAGS) $(TEST_OBJ) -Lmlx -lmlx -lX11 -lXext -lm -o test

clean:
	$(RM) $(OBJ)
	$(RM) $(TEST_OBJ)

fclean: clean
	make clean -C ./mlx
	$(RM) $(NAME)
	$(RM) test

re: fclean $(NAME)

.PHONY: all bonus clean fclean re

.SILENT:
