/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/28 00:06:30 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	close_wait(t_init ishell, t_lst_cmd *mshell)
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
	free(ishell.new_line);
	free_str(ishell.cmd);
	free(ishell.prompt_line);
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

void	cmd_fork(t_lst_cmd *tmp, char **env, int i)
{
	tmp->pipex->child = fork();
	if (tmp->pipex->child == -1)
	{
		write(2, "fork failed\n", 13);
		exit (1);
	}
	if (tmp->pipex->child == 0)
	{
		dup_exec(i);
		exec_cmd(tmp, env);
	}
}
