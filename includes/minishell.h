/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/03 18:51:21 by adaloui          ###   ########.fr       */
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
# include <errno.h>
# include "../libft/libft.h"

# define SUCCESS 0
# define FAILURE 1

extern struct s_lst_cmd	*g_list;

typedef struct s_lst_cmd
{
	char **split_byspace;
	struct s_lst_cmd	*next;
	//char *prompt_line;
	pid_t pid;
	char **envp_2;
	int	exit_value;
	int	unset_minus;
}				t_lst_cmd;

typedef struct s_decompte
{
	int i;
	int j;
}				t_decompte;

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
t_lst_cmd	*create_lst(char *str, t_lst_cmd *lst, int nb_pipe, char **env);
t_lst_cmd	*file_lst(char *split_bypipe, char **env);
int			count_pipe(char *str);
int		size_malloc(char *str);
char	*skip_quote_cmd(char *str);
char	*skip_dquote_arg(char *str);
t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst, char **env);

int	exit_shell(char *buffer, t_lst_cmd *lst);
void	minishell(t_lst_cmd *lst, char **env);

/*	FT_ERRORS_HANDLERS	*/
void	ft_free_charr(char **path);
int		ft_custom_error(char *errstr);
int		ft_system_error(void);

/*	FT_BUILT_IN_CHECKER	*/
int		ft_is_built_in(char *cmd);
int		exec_built_in(char **built_in, char **envp);

/*	FT_PWD	*/
int		ft_builtin_pwd(char **argv);

/*	FT_CD	*/
int		ft_built_in_cd(char **path, char **envp);

/*	FT_EXIT	*/
int		ft_built_in_exit(char **cmd, char **envp);

/*	FT_ENV	*/
void	ft_built_in_env(char **built_in, char **env);

/*	FT_ECHO	*/
int		ft_built_in_echo(char **cmd);

/*	FT_UNSET	*/
int 	ft_built_in_unset(char **cmd, char **envp);

/*	FT_EXPORT	*/
int		ft_built_in_export(char **cmd, char **envp);

/*	FT_GET_VAR_ENV	*/
char	**ft_get_var_env(char **envp, char *str);
char	**ft_get_var_env_2(char **envp, char *var_env);

void		status_child(void);
char		**ft_env_cpy(char **envp, char **envp_2);

#endif