NAME = philosophers
FLAGS = -Wall -Wextra -Werror -g
SRC = main.c

SRC_DIR = src/
OBJ_DIR = .obj/

OBJ_P = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
SRC_P = $(addprefix $(SRC_DIR), $(SRC))
.PHONY: all re clean fclean

all : $(NAME)


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re : fclean
	$(MAKE) all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_P) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(OBJ_P) -o $(NAME)
