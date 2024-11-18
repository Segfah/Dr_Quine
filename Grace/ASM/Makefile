NAME = Grace
FILE_GENERATED = Grace_kid.asm

CC = gcc
CFLAGS = -Wall -Wextra -Werror

CC_ASM = nasm
NASM_FLAGS = -felf64

SRC = Grace.asm
OBJ = $(SRC:%.asm=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -no-pie -nostartfiles $(OBJ) -o $(NAME)
	./$(NAME)

%.o: %.asm
	$(CC_ASM) $(NASM_FLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(FILE_GENERATED) $(NAME)

test: all
	@./$(NAME); \
	if diff $(FILE_GENERATED) $(SRC) > /dev/null; then \
		printf "\033[32m[True]\033[0m\n"; \
	else \
		printf "\033[31m[False]\033[0m\n"; \
	fi
	@$(MAKE) -s fclean

re: fclean all
