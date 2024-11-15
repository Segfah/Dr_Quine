NAME = Grace
FILE_GENERATED = Grace_kid.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = Grace.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(FILE_GENERATED) $(NAME)

test: all
	@./$(NAME); \
	if diff $(FILE_GENERATED) Grace.c > /dev/null; then \
		printf "\033[32m[True]\033[0m\n"; \
	else \
		printf "\033[31m[False]\033[0m\n"; \
	fi
	@rm -f $(FILE_GENERATED) $(NAME)

re: fclean all
