/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/29 19:03:51 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	close_wait(t_lst_cmd *mshell)
{
	t_decompte	index;
	t_lst_cmd	*tmp;

	index.i = -1;
	tmp = mshell;
	while (tmp)
	{
		index.i = -1;
		while (g_list->nb_pipe != 0 && ++index.i < g_list->nb_pipe)
		{
			close(g_list->pfd[index.i][0]);
			close(g_list->pfd[index.i][1]);
		}
		waitpid(tmp->pipex->child, &index.j, 0);
		tmp = tmp->next;
	}
	free_lst(mshell);
	if (WIFEXITED(index.j))
		return (WEXITSTATUS(index.j));
	if (WIFSIGNALED(index.j))
		return (WTERMSIG(index.j) + 128);
	return (index.j);
}

void	dup_exec(int i)
{
	int	k;

	k = -1;
	if (i != 0)
	{
		dup2(g_list->pfd[i - 1][0], 0);
		if (g_list->check_stds == 1)
			dup2(g_list->fd_stdout, STDOUT_FILENO);
	}
	if (i != g_list->nb_pipe)
	{
		if (g_list->check_stds == 0)
			dup2(g_list->pfd[i][1], 1);
	}
	while (g_list->nb_pipe != 0 && ++k < g_list->nb_pipe)
	{
		close(g_list->pfd[k][0]);
		close(g_list->pfd[k][1]);
	}
}

void	exec_cmd(t_lst_cmd *mshell, char **env)
{
	if (mshell->pipex->exec_path == NULL)
	{
		printf("%s : command not found\n", mshell->split_byspace[0]);
		exit(127);
	}
	if (access(mshell->pipex->exec_path, F_OK) == 0)
		execve(mshell->pipex->exec_path, mshell->split_byspace, env);
}
int	ft_is_built(t_lst_cmd *tmp)
{
	const char	*built_in[] = {"pwd", "cd", "exit",
		"export", "env", "unset", NULL};
	int			i;

	i = 0;
	printf("temp built =%s\n", tmp->split_byspace[0]);
	while (built_in[i])
	{
		if (!strcmp(built_in[i], tmp->split_byspace[0]))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	exec_built(t_lst_cmd *mshell, char **env)
{
	if (!ft_strcmp(mshell->split_byspace[0], "pwd"))
		ft_builtin_pwd(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "cd"))  // Non 
		ft_built_in_cd(mshell->split_byspace, env);
	else if (!ft_strcmp(mshell->split_byspace[0], "exit")) // Non
		ft_built_in_exit(mshell);
	else if (!ft_strcmp(mshell->split_byspace[0], "echo"))
		ft_built_echo(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "env"))
		ft_built_in_env(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "export")) // Non
		ft_built_in_export(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "unset")) // Non
		ft_built_in_unset(mshell->split_byspace);
	return (FAILURE);
}

void	cmd_fork(t_lst_cmd *tmp, char **env, int i)
{
	tmp->pipex->child = fork();
	if (tmp->pipex->child == -1)
	{
		write(2, "fork failed\n", 13);
		exit (127);
	}
	if (tmp->pipex->child == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup_exec(i);
		if (ft_is_built_in(tmp->split_byspace[0]) == 0)
		{
				exec_built_in(tmp, env);
				exit(127);
		}
		exec_cmd(tmp, env);
	}
}
