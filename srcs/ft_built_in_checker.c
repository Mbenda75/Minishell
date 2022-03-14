/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:03:44 by user42            #+#    #+#             */
/*   Updated: 2022/03/14 18:54:48 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd", "exit", "env", "export", "echo", "unset", NULL};
	int i;

	i = 0;
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd))
			return (1); 
		i++;
	}
	return (0);
}

int	exec_built_in(char **built_in, char **env)
{
	printf("builtin === %s\n", built_in[0]);
	if (!ft_strcmp(built_in[0], "pwd"))
		ft_builtin_pwd(built_in);
	else if (!ft_strcmp(built_in[0], "cd"))
		ft_built_in_cd(built_in, env);
	else if (!ft_strcmp(built_in[0], "exit"))
		ft_built_in_exit(built_in);
	else if (!ft_strcmp(built_in[0], "echo"))
		ft_built_in_echo(built_in);
	else if (!ft_strcmp(built_in[0], "env"))
		ft_built_in_env(built_in);
	else if (!ft_strcmp(built_in[0], "export"))
		ft_built_in_export(built_in);
	else if (!ft_strcmp(built_in[0], "unset"))
		ft_built_in_unset(built_in);
	else
		return (FAILURE);
}