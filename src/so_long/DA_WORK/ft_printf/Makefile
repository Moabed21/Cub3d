# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabed <moabed@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 18:51:27 by melshata          #+#    #+#              #
#    Updated: 2026/07/18 15:22:08 by moabed           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES =	printf.c \
			ftpf_putstr.c \
			ftpf_putnbr.c \
			ftpf_puthex.c
NAME =		libftprintf.a
CC = cc
CFLAGS = -Werror -Wall -Wextra
OBJ = $(CFILES:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	ar rcs $(NAME) $(OBJ)

# $(NAME) : $(OBJ)
# 	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)
	

fclean:
	rm -f $(OBJ) $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: all clean fclean re