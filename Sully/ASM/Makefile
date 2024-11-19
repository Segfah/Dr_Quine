NAME = Sully

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIE
LDFLAGS = -pie


CC_ASM = nasm
NASM_FLAGS = -felf64

SRC = Sully.asm
OBJ = ${SRC:.asm=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -no-pie $(OBJ) -o $(NAME)


%.o: %.asm
	$(CC_ASM) $(NASM_FLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME)_*

re: fclean all
