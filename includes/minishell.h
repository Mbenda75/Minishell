/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/02 17:32:02 by benmoham         ###   ########.fr       */
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
void	*free_lst(t_lst_cmd *lst);

/* PARSING SHELL */
char	*skip_dquote(char *str);
t_lst_cmd	*create_lst(char *str, t_lst_cmd *lst, int nb_pipe);
t_lst_cmd	*file_lst(char *split_bypipe);
int			count_pipe(char *str);
int		size_malloc(char *str);
char	*skip_dquote_cmd(char *str);
char	*skip_dquote_arg(char *str);
t_lst_cmd	*parsing_shell(char *buffer, t_lst_cmd *lst);

int	exit_shell(char *buffer, t_lst_cmd *lst);
void	minishell(t_lst_cmd *lst, char **env);
#endif