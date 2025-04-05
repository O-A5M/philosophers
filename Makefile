# compilation's variables

CC = cc
CFLAGS = -Wall -Wextra -Werror
THREAD_FLAG = -pthread

# philo's variables

DIR = philo
NAME = $(DIR)/philo
SRC = philo/philo.c philo/philo_parcing.c philo/ft_atoi.c
OBJ = $(SRC:.c=.o)

# philo_bonus's variables

DIR_B = philo_bonus
NAME_B = $(DIR_B)/philo_bonus
SRC_B = philo_bonus/philo_bonus.c
OBJ_B = $(SRC_B:.c=.o)

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
