# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/02 17:13:28 by bhernand          #+#    #+#              #
#    Updated: 2026/07/02 17:13:31 by bhernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRCS        = main.c \
              parsing.c \
              disorder_and_index.c \
              errors.c \
              utils.c \
              operations_swap_push.c \
              operations_rotate.c \
              operations_rev_rotate.c \
              benchmark_display.c \
              sort_router.c \
              sort_simple.c \
              sort_medium.c \
              sort_complex.c

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
