/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:08:32 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/29 00:17:30 by adaloui          ###   ########.fr       */
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
	char				*r_hdc;
	int					nb_pipe;
	int					**pfd;
	int					fd_stdout;
	int					fd_stdin;
	int					hrdc_stdout;
	int					hrdc_stdin;
	int					check_stds;
	int					file_open;
	int					exit_value;
	struct s_env		*next;
}				t_env;

typedef struct s_pipex
{
	char	**split_path;
	char	*line_path;
	char	*exec_path;
	pid_t	child;
}		t_pipex;

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
	struct s_pipex		*pipex;
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

/* 			FUNCT MEMORY */
void		free_str(char **s);
void		*free_lst(t_lst_cmd *lst);
void		*free_env(t_env *lst);
void		free_fd(int **fd);

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
char		*ft_add_content(char *avant_equal, char *after_equal);
char		*ft_add_env_var(char *after_equal, char *env_var);
int			ft_len(char *cmd[]);

/*			INIT SHELL  		*/
t_env		*cpy_env(char **envp);
t_env		*fill_env(char *str);
t_lst_cmd	*create_lst(char *prompt_line, t_lst_cmd *lst);
t_lst_cmd	*fill_lst(char *split_bypipe);
t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst);
t_lst_cmd	*create_norm(t_lst_cmd *lst,
				char **split_bypipe, char *prompt_line);

/* 			MINISHELL 			*/
void		start_minishell(t_init ishell, char **env);
void		minishell( char **env);

/* 			EXEC PART				*/
char		*search_path(t_env *lst);
char		*ft_strcat2(char *dest, char *src);
char		*boucle_path(char **array_path, char **array_cmd);
void		exec_cmd(t_lst_cmd *mshell, char **env);
void		cmd_fork(t_lst_cmd *tmp, char **env, int i);
t_pipex		*init_pipex(char **split_byspace);
int			close_wait(t_init ishell, t_lst_cmd *mshell);
void		dup_exec(int i);
int			init_pfd(t_init ishell);


/*			FT_ERRORS_HANDLERS		*/
void		free_str(char **path);
int			ft_custom_error(char *errstr);
int			ft_system_error(void);

/*			FT_BUILT_IN_CHECKER		*/
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
int			ft_echo_single_dollar(char **cmd, int i);
int			ft_echo_several_dollars(char **cmd, int i);

/*			UTILS_ECHO_2		*/
int			ft_len(char **cmd);
int			ft_count_dollars(char **cmd, int i);

/*			UTILS_ECHO_PRINT_DOLLAR		*/
t_decompte	ft_echo_print_single_dollar(char **split_bydollar,
				t_decompte j_et_s);
t_decompte	ft_init_and_write(char **cmd, int i,
				t_decompte j_et_s);
int			ft_print_exit_value(char **i, t_decompte *j,
				t_decompte *k, char **l);

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

void		status_child(void);
char		**ft_env_cpy(char **envp, char **envp_2);

/*			FT_ERROR_REDIR			*/
int			ft_check_redirection(char *str);

/*			UTILS_REDIR		*/
int			ft_check_if_no_redir(char *str);
int			ft_check_file_existence(char *str);
int			ft_check_space_at_the_end(char *str);
int			ft_check_chevron_grammar_2(char *str);
int			ft_check_chevron_grammar_1(char *str);

/*			UTILS_REDIR_2		*/
int			ft_check_all_redir_errors_norm(char *str);
int			ft_check_all_redir_errors(char *str);

/*			FT_REDIR_HANDLER	*/
int			ft_redir_handler(char *str);
int			ft_heredoc(char **tab, int i);

/*			FT_UTILS_REDIR_CREATE_FILES		*/
int			ft_pas_colle_chevron(char **str, int i);
int			ft_pas_colle_double_chevron(char **str, int i);
int			ft_pas_colle_chevron_inverse(char **str, int i);

/*			FT_PARSE_DOLLAR		*/
char		*ft_transform_dollar(char *str);
char		*ft_modify_newline_content(char **r_value);
char		**ft_transform_dollar_malloc(char *str);
char		**ft_assign_value(char *s_byspace,
				char **r_value, t_decompte *index);
char		*ft_assign_value_2(char **s_bydollar, t_decompte *index);

/*			UTILS_PARSE_DOLLAR		*/
int			ft_count_dollar(char *str);
int			ft_check_env_var_existence(char *complete_var);
char		*ft_change_dollar_var(char *word);
int			ft_is_operator(char str);

/*			FT_NO_CMD		*/
void		ft_handle_dollar_no_cmd(char **split_byspace);
char		*ft_no_cmd_dollar(char *str);
char		*ft_transform_dollar_for_no_cmd(char *str);
int			ft_no_cmd_dollar_check(char *str);

/*			FT_TRANSFORM_REDIR_STR		*/
t_env		*fill_env_2(char *str);
t_env		*cpy_env_2(char **str, t_env *i);
void		ft_free_middle_node_2(t_env *head);
void		ft_free_last_node_2(t_env *temp);
char		*ft_transform_redirection(char *str);
//char		*ft_redir_nrm(t_env *tmp_2);
char		*ft_redir_nrm(char *str, t_env *tmp_2);
void		ft_free_last_node(t_env *temp);
void		ft_free_middle_node(t_env *head);

#endif
