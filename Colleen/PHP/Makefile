NAME = Colleen.php

CC = php

SRC = $(NAME)

.PHONY: all clean fclean test re run

all:
	@echo "No compilation needed for PHP scripts."

clean:
	@echo "No object files to clean for PHP scripts."

fclean: clean
	rm -f tmp_Colleen

run:
	@$(CC) $(SRC)

test:
	@$(CC) $(SRC) > tmp_Colleen; \
	if diff tmp_Colleen $(SRC) > /dev/null; then \
		printf "\033[32m[True]\033[0m\n"; \
	else \
		printf "\033[31m[False]\033[0m\n"; \
	fi
	@rm -f tmp_Colleen

re: fclean all
