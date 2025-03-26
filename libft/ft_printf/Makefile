CFLAGS = -Wall -Werror -Wextra
CC = cc
SRC = ft_putnbr_base.c ft_putuns.c ft_putchar_fd_int.c ft_putnbr_fd_int.c ft_putstr_fd_int.c ft_printf.c ft_putadr.c
OBJ = $(SRC:.c=.o)
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
