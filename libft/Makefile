# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 11:00:30 by adaloui           #+#    #+#              #
#    Updated: 2022/03/03 18:19:22 by adaloui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		*.c

OBJ =		${SRCS:.c=.o}

BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstnew.c ft_lstsize.c

BONUS_OBJ		= $(BONUS:.c=.o)

NAME =		libft.a
CC =		gcc

.c.o:
		${CC} -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):
		@${CC} -Wall -Wextra -Werror -c ${SRCS}
		@ar rc ${NAME}   ${OBJ}
		@ranlib ${NAME}

clean:
		@rm -f ${OBJ} $(BONUS_OBJ)

fclean:		clean
		@rm -f ${NAME}

bonus:			$(OBJ) $(BONUS_OBJ)
				@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

re:		fclean ${NAME}

.PHONY:		all clean fclean re bonus
