# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 15:23:23 by ohosnedl          #+#    #+#              #
#    Updated: 2023/09/11 15:14:52 by ohosnedl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a

SOURCES = ft_printf.c print_char.c print_digit_lower.c\
			print_digit_upper.c print_str.c print_pointer.c\

OBJECTS = $(SOURCES:.c=.o)

CC 			= gcc

CFLAGS 		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJECTS)
			ar rcs $(NAME) $(OBJECTS)

clean:		
			rm -rf $(OBJECTS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
