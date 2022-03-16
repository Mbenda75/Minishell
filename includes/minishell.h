/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/16 16:25:32 by benmoham         ###   ########.fr       */
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
# include <stdbool.h>

# define SUCCESS 0
# define FAILURE 1

extern struct s_env	*g_list;

typedef struct s_env
{
	char				*content;
	int					index_env;
	int					limit_free;
	char				**env_2;
	struct s_lst_cmd	*tmp;
	struct s_env		*next;
}				t_env;

typedef struct s_pipex
{
	char	**split_path;
	char	*line_path;
	char	*exec_path;
	int		nb_cmd;
	int		*pfd;
	pid_t	child;
}		t_pipex;

typedef struct s_redir
{
	int	redirection_normal;
	int	redirection_inverse;
	int	double_red_norm;
	int	double_red_inv;
}				t_redir;

typedef struct s_init
{
	char	*pwd;
	char	*new_line;
	char	*prompt_line;
	char	**cmd;
}			t_init;

typedef struct s_lst_cmd
{
	char				**split_byspace;
	struct s_lst_cmd	*next;
	int					exit_value;
}				t_lst_cmd;

typedef struct s_decompte
{
	int	i;
	int	j;
	int	l;
}				t_decompte;

/*			FT_SIGNALS			*/
void		ft_signals(void);
void		ft_signals_handler(int signal);

/* FUNCT MEMORY */
void		free_str(char **s);
void		*free_lst(t_lst_cmd *lst);
void		*free_env(t_env *lst);

/* 			PARSING SHELL		 */
char		*skip_quote(char *str);
int			check_first_quote(char *str);

int			count_pipe(char *str);
int			size_malloc(char *str);
int			len_lst(t_lst_cmd *lst);
int			check_pipe(char *str);

int			ft_find_the_equal(char *str);
int			ft_find_where_is_equal(char *str);
int			ft_check_variable_after_equal(char *cmd);
int			ft_check_variable_before_equal(char *cmd);
char		*ft_trim_name(char *cmd);
char 		*ft_add_content(char *avant_equal, char *after_equal);


/*			INIT SHELL  		*/
t_env		*cpy_env(char **envp);
t_env		*file_env(char *str, int i);
t_lst_cmd	*create_lst(char *prompt_line, int nb_pipe, t_lst_cmd *lst);
t_lst_cmd	*file_lst(char *split_bypipe);
t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst);

/* 			MINISHELL 			*/
void		start_minishell(t_init ishell, char **env);
void		minishell( char **env);

/* 			PIPEX				*/
char		*search_path(t_env *lst);
char		*ft_strcat2(char *dest, char *src);
char		*boucle_path(char **array_path, char **array_cmd);
int			builtin_or_exec(t_lst_cmd *mshell, char **env, t_init ishell);

/*		FT_ERRORS_HANDLERS		*/
void		ft_free_charr(char **path);
int			ft_custom_error(char *errstr);
int			ft_system_error(void);

/*		FT_BUILT_IN_CHECKER		*/
int			ft_is_built_in(char *cmd);
int			exec_built_in(t_lst_cmd *mshell, char **env);
/*			FT_PWD				*/
int			ft_builtin_pwd(char **argv);

/*			FT_CD				*/
int			ft_built_in_cd(char **path, char **envp);

/*			FT_EXIT			*/
int			ft_built_in_exit(t_lst_cmd *mshell);

/*			FT_ENV				*/
void		ft_built_in_env(char **built_in);

/*			FT_ECHO			*/
int			ft_built_echo(char *args[]);

/*			FT_UNSET				*/
int			ft_built_in_unset(char **cmd);

/*			FT_EXPORT				*/
int			ft_built_in_export(char **cmd);

/*			FT_GET_VAR_ENV			*/
char		**ft_get_var_env(char **envp, char *str);
char		**ft_get_var_env_2(char **envp, char *var_env);

/*			FT_PIPE_CMD					*/
t_redir		*ft_count_simple_redirect(char *str);

void		status_child(void);
char		**ft_env_cpy(char **envp, char **envp_2);
#endif