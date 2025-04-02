# compilation's variables

CC = cc
CFLAGS = -Wall -Wextra -Werror
THREAD_FLAG = -pthread

# philo's variables

DIR = philo
NAME = $(DIR)/philo
SRC = philo/philo.c
OBJ = $(SRC:.c=.o)

# philo_bonus's variables

DIR_B = philo_bonus
NAME_B = $(DIR_B)/philo_bonus
SRC_B = philo_bonus/philo_bonus.c
OBJ_B = $(SRC_B:.c=.o)

# libft's variables

LIBFT_N = libft.a
LIBFT_D = libft
LIBFT = $(LIBFT_D)/$(LIBFT_N)

# ft_printf's variables

PRINTF_N = libftprintf.a
PRINTF_D = ft_printf
PRINTF = $(PRINTF_D)/$(PRINTF_N)

# the rules

all: $(LIBFT) $(PRINTF) $(NAME)

bonus: $(LIBFT) $(PRINTF) $(NAME_B)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(THREAD_FLAG) $(PRINTF) $(LIBFT) $(OBJ) -o $(NAME)

$(LIBFT_N):
	$(MAKE) -C $(LIBFT_D) all

$(PRINTF_N):
	$(MAKE) -C $(PRINTF_D) all

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(THREAD_FLAG) $(OBJ_B) -o $(NAME_B)

clean:
	rm -rf $(OBJ) $(OBJ_B)
	$(MAKE) -C $(LIBFT_D) clean
	$(MAKE) -C $(PRINTF_D) clean

fclean: clean
	rm -rf $(NAME) $(NAME_B)
	$(MAKE) -C $(LIBFT_D) fclean
	$(MAKE) -C $(PRINTF_D) fclean

re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ) $(OBJ_B) $(LIBFT) $(PRINTF)
