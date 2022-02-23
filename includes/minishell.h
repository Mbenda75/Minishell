/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/02/23 19:12:15 by benmoham         ###   ########.fr       */
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

typedef struct s_lst_cmd
{
	char **split_byspace;
	struct s_lst_cmd	*next;
}				t_lst_cmd;

enum e_token
{
	TOKEN_PIPE = 1,
	TOKEN_RLEFT = 2,
	TOKEN_RRIGHT = 3,
	TOKEN_ALEFT = 4,
	TOKEN_ARIGHT = 5,
	TOKEN_SQUOTE = 6,
	TOKEN_DQUOTE = 7,
	TOKEN_WORD = 8,
};

/*	FT_SIGNALS	*/
void	ft_signals(void);
void	ft_signals_handler(int signal);

/* FUNCT MEMORY */
void	free_str(char **s);

#endif