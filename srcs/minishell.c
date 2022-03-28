/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:46:47 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/28 16:40:55 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_all_fd(void)
{
	dup2(g_list->fd_stdout, STDOUT_FILENO);
	dup2(g_list->fd_stdin, STDIN_FILENO);
	close(g_list->file_open);
	close(g_list->fd_stdout);
	close(g_list->fd_stdin);
	g_list->check_stds = 0;
}

void	start_minishell(t_init ishell, char **env)
{
	t_lst_cmd	*mshell;
	t_lst_cmd	*tmp;
	int			i;

	i = -1;
	mshell = NULL;
	mshell = init_shell(ishell.new_line, mshell);
	tmp = mshell;
	while (tmp)
	{
		if (ft_is_built_in(mshell->split_byspace[0]) == 0)
			exec_built_in(mshell, env);
		else
			cmd_fork(tmp, env, ++i);
		tmp = tmp->next;
	}
	if (g_list->check_stds == 1)
		ft_close_all_fd();
	g_list->exit_value = close_wait(ishell, mshell);
}

char	*get_prompt(void)
{
	char	*tmp;
	char	*ret;

	tmp = getcwd(NULL, 0);
	ret = ft_strjoin(tmp, " ");
	free(tmp);
	return (ret);
}

int	init_pfd(t_init ishell)
{
	int	i;

	g_list->nb_pipe = count_pipe(ishell.new_line);
	if (g_list->nb_pipe != 0)
	{
		i = -1;
		g_list->pfd = NULL;
		g_list->pfd = malloc(sizeof(int **) * g_list->nb_pipe);
		if (!g_list->pfd)
			return (FAILURE);
		while (++i < g_list->nb_pipe)
		{
			g_list->pfd[i] = malloc(sizeof(int) * 2);
			if (!g_list->pfd)
				return (FAILURE);
		}
		i = -1;
		while (++i < g_list->nb_pipe)
			pipe(g_list->pfd[i]);
	}
	return (SUCCESS);
}

void	minishell(char **env)
{
	
	t_init	ishell;
	memset(&g_list, 0, sizeof(g_list));
	g_list = cpy_env(env);
	while (1)
	{
		ishell.pwd = get_prompt();
		ishell.prompt_line = readline(ishell.pwd);
		ishell.cmd = ft_split(ishell.prompt_line, ' ');
		free(ishell.pwd);
		if (ishell.cmd[0] == NULL)
		{
			ft_putstr_fd(NULL, 0);
			free_str(ishell.cmd);
		}
		else if (ishell.cmd[0] != NULL)
		{
			add_history(ishell.prompt_line);
			if (check_pipe(ishell.prompt_line) == FAILURE
				|| if_noquote(ishell.prompt_line) == FAILURE
				|| ft_check_redirection(ishell.prompt_line) == FAILURE
				|| ft_no_cmd_dollar_check(ishell.prompt_line) == FAILURE)
			{
				free_str(ishell.cmd);
				free(ishell.prompt_line);
			}
			else
			{
				ishell.new_line = skip_quote(ishell.prompt_line);
				ishell.new_line = ft_no_cmd_dollar(ishell.new_line);
				init_pfd(ishell);
				start_minishell(ishell, env);
				if (g_list->nb_pipe != 0)
					free_fd(g_list->pfd);
			}
		}
	}
}
