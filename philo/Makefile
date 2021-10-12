# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melghoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 14:00:48 by melghoud          #+#    #+#              #
#    Updated: 2021/10/10 13:09:47 by melghoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


PRGM = philo
SRCS = philo.c routine.c supervisor.c utils.c

all: $(PRGM)

$(PRGM): $(SRCS)
	gcc -pthread -Wall -Wextra -Werror $(SRCS) -o $(PRGM)

clean:
	rm -f $(PRGM)

fclean: clean

re: clean all
