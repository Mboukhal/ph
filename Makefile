# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/17 13:58:58 by mboukhal          #+#    #+#              #
#    Updated: 2022/05/15 13:02:50 by mboukhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.DEFAULT_GOAL		= all
NAME				= philo
CFILES				= main.c philo_utils.c emulation.c #thread_exec.c

CFLAGS				= -Wall -Wextra -Werror

OBJS			= $(CFILES:.c=.o)

clean:
	@$(RM) -rf $(OBJS)

fclean: clean
	@$(RM) -rf $(NAME)

re: fclean all

.c.o:
	@$(CC) $(CFLAGS) -c $< 

$(NAME):$(OBJS)
	@$(CC) $(CFLAGS) -lpthread -o $(NAME) $(OBJS) -g -fsanitize=address
	
all: $(NAME) clean

.PHONY: re fclean all clean
