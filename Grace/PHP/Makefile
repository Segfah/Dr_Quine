NAME = Grace.php
FILE_GENERATED = Grace_kid.php

CC = php

SRC = $(NAME)

.PHONY: all clean fclean test re run

all:
	@echo "No compilation needed for PHP scripts."

run:
	@$(CC) $(SRC)

clean:
	@echo "No object files to clean for PHP scripts."

fclean: clean
	rm -f $(FILE_GENERATED)

test:
	@$(CC) $(SRC)
	@if diff $(FILE_GENERATED) Grace.php > /dev/null; then \
		printf "\033[32m[True]\033[0m\n"; \
	else \
		printf "\033[31m[False]\033[0m\n"; \
	fi
	@rm -f $(FILE_GENERATED)
re: fclean all
