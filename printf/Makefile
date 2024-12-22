
NAME = libftprintf.a
SOURCES = ft_printf.c ft_putnbr_fd.c ft_strlen.c ft_strdup.c ft_printhex.c
OFILES = $(SOURCES:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror
$(NAME): $(OFILES)
	ar -rcs $(NAME) $(OFILES)
all: $(NAME)


%.o: %.c
	$(CC) $(FLAGS) -c $< -I. -o $@


clean:
	rm -f $(OFILES)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all, clean, fclean, re
