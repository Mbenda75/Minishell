/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/14 10:51:25 by benmoham         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define SUCCESS 0
# define FAILURE 1

extern struct s_env	*g_list;

typedef struct s_env
{
	char *content;
	int index_env;
	int limit_free;
	struct s_env *next;
}				t_env;

typedef struct s_pipex
{
	char **split_path;
	char *line_path;
	char *exec_path;
	int  nb_cmd;
	int pfd[2];
	pid_t		child;
}		t_pipex;


typedef struct s_redirection
{
	int redirection_normal;
	int redirection_inverse;
	int double_red_norm;
	int double_red_inv;
}				t_redirection;


typedef struct s_init
{
	char 	*pwd;
	char 	*new_line;
	char 	*prompt_line;
	char 	**cmd;
}			t_init;

typedef struct s_lst_cmd
{
	char **split_byspace;
	struct s_lst_cmd	*next;
	int	exit_value;
}				t_lst_cmd;

typedef struct s_decompte
{
	int i;
	int j;
	int l;
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
void  *free_env(t_env *lst);

/* PARSING SHELL */
char	*skip_dquote(char *str);
t_lst_cmd	*create_lst(char *prompt_line, int nb_pipe, t_lst_cmd *lst, char **env);
t_lst_cmd	*file_lst(char *split_bypipe, char **env);
int			count_pipe(char *str);
int		size_malloc(char *str);
char	*skip_squote_cmd(char *str);
char	*skip_dquote_cmd(char *str);
t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst, char **env);
int check_quote(char *str);


void	minishell( char **env);
t_env	*cpy_env(char **envp);
t_env *file_env(char *str, int i);

/* 			PIPEX				*/
char 	*search_path(t_env *lst);
char	*ft_strcat2(char *dest, char *src);
char	*boucle_path(char **array_path, char **array_cmd);
int		start_exec(t_pipex *pipex, t_lst_cmd *mshell, char **env);

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
int		ft_built_in_exit(char **cmd);

/*	FT_ENV	*/
void	ft_built_in_env(char **built_in);

/*	FT_ECHO	*/
int		ft_built_in_echo(char **cmd);

/*	FT_UNSET	*/
int 	ft_built_in_unset(char **cmd);

/*	FT_EXPORT	*/
int		ft_built_in_export(char **cmd);

/*	FT_GET_VAR_ENV	*/
char	**ft_get_var_env(char **envp, char *str);
char	**ft_get_var_env_2(char **envp, char *var_env);

/*	FT_PIPE_CMD	*/
t_redirection	*ft_count_simple_redirect(char *str);


void		status_child(void);
char		**ft_env_cpy(char **envp, char **envp_2);
#endif