NAME = philo
FLAGS = -Wall -Wextra -Werror -g
SANITIZE_FLAGS = -Wall -Wextra -g -fsanitize=thread
DEBUG_FLAGS = -Wall -Wextra -g -D DEBUG=1

NL_SRC = ft_calloc.c ft_atoi.c ft_ctype.c ft_putstr_fd.c
M_SRC = main.c init.c destroy.c actions.c action_utils.c utils.c parsing.c \
		monitor.c

N_INC = philosophers.h

P_NL = $(addprefix $(NOT_LIBFT_DIR), $(NL_SRC))

SRC_DIR = src/
OBJ_DIR = .obj/
INC_DIR = inc/
NOT_LIBFT_DIR = not_libft/
NOT_PRINTF_DIR = ft_printf/



INC = $(addprefix $(INC_DIR), $(N_INC))
SRC = $(P_NL) $(M_SRC)
OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

.PHONY: all re clean fclean

all : $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re : fclean
	$(MAKE) all

san : fclean
	$(MAKE) all "FLAGS=$(SANITIZE_FLAGS)"
	$(MAKE) clean

debug :
	$(MAKE) re FLAGS+="-D DEBUG=1 -g"
	$(MAKE) clean


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(NOT_LIBFT_DIR)
	mkdir -p $(OBJ_DIR)$(NOT_PRINTF_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC) | $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ) | $(OBJ_DIR) 
	$(CC) $(FLAGS) $(OBJ) -I$(INC_DIR) -o $(NAME)

