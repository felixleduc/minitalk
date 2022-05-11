# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleduc <marvin@42quebec.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 11:45:50 by fleduc            #+#    #+#              #
#    Updated: 2022/05/11 14:05:34 by fleduc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRV = server
CLI = client

CC = @gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRCS_CLI = client.c
SRCS_SRV = server.c
SRCS = utils.c

OBJS_CLI = $(SRCS_CLI:.c=.o)
OBJS_SRV = $(SRCS_SRV:.c=.o)
OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(OBJS)
	$(MAKE) $(SRV)
	$(MAKE) $(CLI)

$(SRV): $(OBJS_SRV)
	$(CC) $(CFLAGS) -o server $(OBJS_SRV) $(OBJS)

$(CLI): $(OBJS_CLI)
	$(CC) $(CFLAGS) -o client $(OBJS_CLI) $(OBJS)

clean:
	@$(RM) $(OBJS_CLI) $(OBJS_SRV) $(OBJS)

fclean: clean
	@$(RM) $(SRV) $(CLI)

re: fclean
	$(MAKE)

.PHONY: re fclean clean all
