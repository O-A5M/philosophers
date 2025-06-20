# compilation's variables

CC = cc
CFLAGS = -Wall -Wextra -Werror
THREAD_FLAG = -pthread

# philo's variables

DIR = philo
NAME = $(DIR)/philo
SRC = philo/main/philo.c philo/main/philo_utils.c philo/parsing/philo_parsing.c philo/parsing/philo_parsing_utils.c \
	  philo/simulation/philo_init.c philo/simulation/philo_init_utils.c philo/simulation/philo_routine.c
OBJ = $(SRC:.c=.o)

# the rules

all: $(NAME)

bonus: $(NAME_B)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(THREAD_FLAG) $(PRINTF) $(LIBFT) $(OBJ) -o $(NAME)

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(THREAD_FLAG) $(OBJ_B) -o $(NAME_B)

clean:
	rm -rf $(OBJ) $(OBJ_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ) $(OBJ_B)
