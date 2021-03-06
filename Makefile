# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 08:05:34 by adaloui           #+#    #+#              #
#    Updated: 2022/03/29 13:50:17 by benmoham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_OS = $(shell uname)

ifeq ($(NAME_OS), Darwin)
        SRC = srcs/*.c libft/*.c
        NAME_OS = MAC
endif
ifeq ($(NAME_OS), Linux)
        SRC = srcs/*.c libft/*.c
endif

OBJ = *.o

FLAGS = -Wall -Wextra -Werror -fsanitize=address

LIBFT_A = libft.a
LIBFT_DOSSIER = libft/
LIBFT  = $(addprefix $(LIBFT_DOSSIER), $(LIBFT_A))

WHITE ='\033[0m'
BLUE ='\033[36m'
CYAN ='\033[1;32m'
RED = '\033[0;31m'


all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CYAN) "Compilation en cours de $(NAME) crée par $(RED)benmoham et adaloui$(CYAN) sur l'OS \"$(NAME_OS)\"" $(WHITE)
	@make  --no-print-directory -C $(LIBFT_DOSSIER)
	@gcc $(FLAGS) $(LIBFT) $(OBJ) -o $(NAME) -lreadline -ggdb3 -std=c11
	@echo ""
	@echo $(BLUE)"Tout a été compilé avec succès ! -"$(WHITE)

$(OBJ): $(SRC)
	@echo $(CYAN) "Creation des fichiers .o." $(WHITE)
	@gcc $(FLAGS) -g -c $(SRC)

clean:
	@echo "Suppression en cours des fichiers .o de $(NAME) et de la libft"
	@echo $(CYAN) "Suppression des fichiers .o de $(NAME)." $(WHITE)
	@echo $(CYAN) "Suppression des fichiers .o de la libft." $(WHITE)
	@rm -f $(OBJ)
	@make --no-print-directory -C $(LIBFT_DOSSIER) clean
	@echo "Nettoyage des fichiers .o effectué"

fclean: clean
	@echo $(CYAN) "Suppression du logiciel $(NAME)." $(WHITE)
	@rm -rf $(NAME)
	@make --no-print-directory -C $(LIBFT_DOSSIER) fclean
	@echo "Tout a été supprimé !"
	
re: fclean all

.PHONY:		all clean fclean re bonus