# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/17 13:58:58 by mboukhal          #+#    #+#              #
#    Updated: 2022/05/16 20:46:40 by mboukhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.DEFAULT_GOAL		= all
NAME				= philo
CFILES				= main.c philo_utils.c emulation.c #thread_exec.c

CFLAGS				= -Wall -Wextra -Werror

OBJS				= $(CFILES:.c=.o)

#################################################
#	echo info
#################################################
RED 				=\033[0;31m # Red
GREEN 				=\033[0;32m # Green
NC					=\033[0m\n$(S) # No Color
SPACER 				= '_'
S					=`python -c "print $(SPACER) * 34"`
ECHO_CLEAN			=echo "$(OBJS)" | tr '\n' '\0' | tr ' ' '\n';\
					echo "\t\t $(RED)CLEAN!$(NC)"

ECHO_ALL			=echo "$(OBJS)" | tr '\n' '\0' | tr ' ' '\n';\
					 echo " \t\t$(GREEN)Created!$(NC)"| tr '_' '.';\
					 echo "$(NAME) \t\t\t$(GREEN)COMPILED!$(NC)"

ECHO_FCLEAN			=echo "\n$(NAME)"; $(ECHO_CLEAN);\
					 echo "$(NAME)   \t\t$(RED)FCLEAN!$(NC)"
#################################################


clean:
	@ $(RM) -rf $(OBJS)
	@ $(ECHO_CLEAN)
	
fclean:
	@ $(RM) -rf $(OBJS); $(RM) -rf $(NAME)
	@ $(ECHO_FCLEAN)

re: fclean all

.c.o:
	@ $(CC) $(CFLAGS) -c $< 

$(NAME):$(OBJS)
	@ $(CC) $(CFLAGS) -lpthread -o $(NAME) $(OBJS) -g -fsanitize=address
	@ $(ECHO_ALL)
	
all: $(NAME) clean

.PHONY: re fclean all clean
