NAME = Colleen

CC = gcc
CFLAGS = -Wall -Wextra -Werror

CC_ASM = nasm
NASM_FLAGS = -felf64

SRC = Colleen.asm
OBJ = $(SRC:%.asm=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -no-pie $(OBJ) -o $(NAME)

%.o: %.asm
	$(CC_ASM) $(NASM_FLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

test: all
	@./$(NAME) > tmp_Colleen; \
	if diff tmp_Colleen $(SRC) > /dev/null; then \
		printf "\033[32m[True]\033[0m\n"; \
	else \
		printf "\033[31m[False]\033[0m\n"; \
	fi
	@rm -f tmp_Colleen

re: fclean all
