NAME = Sully

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = Sully.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.asm
	$(CC_ASM) $(NASM_FLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME)_*

re: fclean all
