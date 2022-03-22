/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:03:44 by user42            #+#    #+#             */
/*   Updated: 2022/03/22 16:30:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd", "exit", "env", "export", "echo", "unset", NULL};
	int			i;

	i = 0;
	if (!cmd)
		return (0);
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int	exec_built_in(t_lst_cmd *mshell, char **env)
{
	printf("builtin === %s\n", mshell->split_byspace[0]);
	if (!ft_strcmp(mshell->split_byspace[0], "pwd"))
		ft_builtin_pwd(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "cd"))
		ft_built_in_cd(mshell->split_byspace, env);
	else if (!ft_strcmp(mshell->split_byspace[0], "exit"))
		ft_built_in_exit(mshell);
	else if (!ft_strcmp(mshell->split_byspace[0], "echo"))
		ft_built_echo(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "env"))
		ft_built_in_env(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "export"))
		ft_built_in_export(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "unset"))
		ft_built_in_unset(mshell->split_byspace);
	else
		return (FAILURE);
}
