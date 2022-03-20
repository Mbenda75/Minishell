/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/20 16:34:21 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int *init_pipe(int count)
{
	int *fd;
	int i;
	
	fd = malloc(sizeof(int) * count - 1);
	i = 0;
	while (i < count - 1)
	{
		
		pipe(fd[i * 2]);
		i++;
	}
	return (fd);	
} */

int	builtin_or_exec(t_lst_cmd *mshell, char **env, t_init ishell)
{
	t_pipex	*pipex;
	pid_t i;
	int status;

	pipex = NULL;
	if (ft_is_built_in(mshell->split_byspace[0]) == 1)
		exec_built_in(mshell, env);
	else
	{
		pipex = malloc(sizeof(t_pipex));
		pipex->line_path = search_path(g_list);
		pipex->split_path = ft_split(pipex->line_path, ':');
		pipex->exec_path = boucle_path(pipex->split_path, mshell->split_byspace);
		printf("split_path == %s\n", pipex->exec_path);
		if (pipex->exec_path == NULL)
		{
			printf("exit exec\n");
			free_str(pipex->split_path);
			free(pipex->exec_path);
			free(pipex);
			return (1);
		}
		pipex->child = fork();
		if (pipex->child == -1)
		{
			write(2, "fork failed\n", 13);
			exit (1);
		}
		if (pipex->child == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (access(pipex->exec_path, F_OK) == 0)
				execve(pipex->exec_path, mshell->split_byspace, env);
		}
		i = waitpid(pipex->child, &status, 0);
		free_str(pipex->split_path);
		free(pipex->exec_path);
		free(pipex);
		if (WIFEXITED(status))
    		return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
    		return (WTERMSIG(status) + 128);
	}
	return (0);
}
