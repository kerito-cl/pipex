NAME = pipex
SOURCES = main.c ft_split.c utils.c children.c error.c
OFILES = $(SOURCES:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(FLAGS) $(OFILES) -o $(NAME) -L./printf -lftprintf

%.o: %.c
	$(CC) $(FLAGS) -c $< -I. -o $@

clean:
	rm -f $(OFILES)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all, clean, fclean, re
