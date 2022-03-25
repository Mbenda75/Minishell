/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/25 17:06:50 by benmoham         ###   ########.fr       */
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
	int					nb_pipe;
	int					**pfd;
	int					exit_value;
	int					savefd[2];
	struct s_env		*next;
}				t_env;

typedef struct s_pipex
{
	char	**split_path;
	char	*line_path;
	char	*exec_path;
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
	struct s_pipex 		*pipex;
	int 				savefd[2];
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
void	free_fd(int **fd);


/* 			PARSING SHELL		 */
char		*skip_quote(char *str);
int			check_first_quote(char *str);
int			if_noquote(char *str);

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
char 		*ft_add_env_var(char *after_equal, char *env_var);
int			ft_len(char *cmd[]);



/*			INIT SHELL  		*/
t_env		*cpy_env(char **envp);
t_env		*fill_env(char *str);
t_lst_cmd	*create_lst(char *prompt_line, t_lst_cmd *lst);
t_lst_cmd	*fill_lst(char *split_bypipe);
t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst);
t_lst_cmd	*create_norm(t_lst_cmd *lst, char **split_bypipe, char *prompt_line);


/* 			MINISHELL 			*/
void		start_minishell(t_init ishell, char **env);
void		minishell( char **env);

/* 			EXEC PART				*/
char		*search_path(t_env *lst);
char		*ft_strcat2(char *dest, char *src);
char		*boucle_path(char **array_path, char **array_cmd);
void		exec_cmd(t_lst_cmd *mshell, char **env);
void		cmd_fork(t_lst_cmd *tmp, char **env, int i);
t_pipex 	*init_pipex(char **split_byspace);
void		close_wait(t_init ishell, t_lst_cmd *mshell);
void		dup_exec(int i);
void		*init_pfd(t_init ishell);



/*		FT_ERRORS_HANDLERS		*/
void		free_str(char **path);
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

/*			UTILS_ECHO		*/
int 		ft_echo_single_dollar(char **cmd, int i, t_env *echo_env);
int			ft_echo_several_dollars(char **cmd, int i, t_env *echo_env);

/*			UTILS_ECHO_2		*/
int			ft_len(char **cmd);
int			ft_count_dollars(char **cmd, int i);

/*			FT_UNSET				*/
int			ft_built_in_unset(char **cmd);

/*			FT_EXPORT				*/
int			ft_built_in_export(char **cmd);

/*			UTILS_EXPORT	*/
int			ft_find_dollars(char *str);
int			ft_find_where_is_equal(char *str);
int			ft_check_variable_after_equal(char *cmd);
int			ft_check_variable_before_equal(char *cmd);
int			ft_find_the_equal(char *str);

/*			FT_GET_VAR_ENV			*/
char		**ft_get_var_env(char **envp, char *str);
char		**ft_get_var_env_2(char **envp, char *var_env);

/*			FT_PIPE_CMD					*/
int			ft_check_redirection(char *str);
t_redir		ft_count_redirection(char *str);


void		status_child(void);
char		**ft_env_cpy(char **envp, char **envp_2);

/*			FT_UTILS_REDIR		*/
int 		ft_check_all_redir_errors(char *str);

/*			FT_UTILS_REDIR_CREATE_FILES		*/
int			ft_pas_colle_chevron(char **str, int i);
int			ft_pas_colle_double_chevron(char **str, int i);
int			ft_pas_colle_chevron_inverse(char **str, int i);

/*			FT_PARSE_DOLLAR		*/
char		*ft_transform_dollar(char *str);
int			ft_find_where_is_dollars(char *str);
int			ft_find_dollars(char *str);
char		*ft_transform_dollar_2(char *str);
int			ft_checK_env_var_existence(char *complete_var);
char		*ft_change_dollar_var(char *word);

#endif
