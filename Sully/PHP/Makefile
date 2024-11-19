NAME = Sully

SRC = Sully.php

.PHONY: all clean fclean test re run

all:
	@echo "No compilation needed for PHP scripts."

clean:
	@echo "No object files to clean for PHP scripts."

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME)_*

run:
	php $(SRC)

re: fclean all
