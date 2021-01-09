NAME = interact

INCLUDE = titans.h

CC = clang
LIB = -lgmp -lcurl
CFLAGS = -Wall -Werror -Wextra

SRC =	main.c utils.c int_request/getBalance.c int_request/unForbidden.c int_request/unlockAccount.c int_request/withdrawReward.c
OBJ =	$(SRC:.c=.o)

.PHONY: clean fclean re

all: $(OBJ) $(INCLUDE)
	$(CC) $(OBJ) -o $(NAME) $(LIB)

clean:
	@echo "Suppression des objets"
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo "Suppression de $(NAME)"
	@/bin/rm -f $(NAME)

re: clean all
