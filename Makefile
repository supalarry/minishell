# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lskrauci <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/16 13:04:01 by lskrauci      #+#    #+#                  #
#    Updated: 2019/02/16 13:04:03 by lskrauci      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./srcs/*.c

HEADER = ./includes/

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -o $(NAME) $(SRCS) -I $(HEADER) -L ./libft/ -lft -Wall -Wextra -Werror
clean:
	make -C ./libft clean
	rm -f *.o

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
