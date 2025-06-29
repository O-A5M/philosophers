NAME	= philo
CC	= gcc
CFLAGS	= -Werror -Wall -Wextra -pthread

SRC_PATH = sources/
OBJ_PATH = objects/

SRC	= philo_main.c philo_parsing.c philo_grim_reaper.c philo_time.c philo_philosopher.c philo_init.c philo_output.c philo_exit.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ	= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
