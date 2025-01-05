#HEADER

NAME = push_swap

LIBFTDIR= ./full_libft

CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRC= main.c read_into_list_char.c check_input.c utils.c swaps.c push.c reverse.c rotate.c sort.c sort3.c bigger_sort.c push_back.c
OBJ = $(SRC:.c=.o)

LIBFTA= full_libft/libfull_libft.a


$(NAME): libft
	$(CC) $(CFLAGS) $(SRC) $(LIBFTA) -o $(NAME)

all: $(NAME)

libft:
	@make -C full_libft

clean:
	rm -f $(OBJ)
	@cd $(LIBFTDIR) && make clean

fclean: clean
	rm -f $(NAME)
	@cd $(LIBFTDIR) && make clean && make fclean

re: fclean all

.PHONY: all clean fclean re libft mlx-linux mac