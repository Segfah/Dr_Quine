NAME = Colleen

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = Colleen.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

test: all
	@./$(NAME) > tmp_Colleen; \
	if diff tmp_Colleen Colleen.c > /dev/null; then \
		printf "\033[32m[True]\033[0m\n"; \
	else \
		printf "\033[31m[False]\033[0m\n"; \
	fi
	@rm -f tmp_Colleen

re: fclean all
