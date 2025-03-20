# compilation's variables

CC = cc
CFLAGS = -Wall -Wextra -Werror
THREAD_FLAG = -pthread

# philo's variables

NAME = philo
SRC = philo/philo.c
OBJ = $(SRC:.o=.c)

# philo_bonus's variables

NAME_B = philo_bonus
SRC_B = philo_bonus/philo_bonus.c
OBJ_B = $(SRC_B:.o=.c)

all: $(NAME)

$(NAME): $(OBJ)
	$(cc) $(CFLAGS) $(THREAD_FLAG) $(OBJ) -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(THREAD_FLAG) $(OBJ_B) -o $(NAME_B)

clean:
	rm -rf $(OBJ) $(OBJ_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ) $(OBJ_B)
