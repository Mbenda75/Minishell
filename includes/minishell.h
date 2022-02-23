/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/02/23 15:12:39 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define SUCCESS 0
# define FAILURE 1
# define NB_TOKEN 14

typedef struct s_lst_cmd
{
	char **split_byspace;
	struct s_lst_cmd	*next;
}				t_lst_cmd;

enum e_token
{
	TOKEN_ERROR = -1,
	TOKEN_BLANK = 0,
	TOKEN_NEWLINE = 1,
	TOKEN_SEMICOLON = 2,
	TOKEN_PIPE = 3,
	TOKEN_RLEFT = 4,
	TOKEN_RRIGHT = 5,
	TOKEN_ALEFT = 6,
	TOKEN_ARIGHT = 7,
	TOKEN_COMMENT = 8,
	TOKEN_SQUOTE = 9,
	TOKEN_DQUOTE = 10,
	TOKEN_ESCAPE = 11,
	TOKEN_VAR = 12,
	TOKEN_WORD = 13
};

/*	FT_SIGNALS	*/
void	ft_signals(void);
void	ft_signals_handler(int signal);

/* FUNCT MEMORY */
void	free_str(char **s);

#endif