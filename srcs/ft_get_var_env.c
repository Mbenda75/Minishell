/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:21:19 by user42            #+#    #+#             */
/*   Updated: 2022/03/27 23:23:05 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_get_var_env(char **envp, char *var_env)
{
	char	**location;
	char	*str;

	str = "/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin";
	while (*envp)
	{
		if (ft_strnstr(*envp, var_env, ft_strlen(var_env)))
		{
			while (**envp != '/')
				*envp += 1;
			location = ft_split(*envp, ':');
			return (location);
		}
		envp++;
	}
	location = ft_split(str, ':');
	return (location);
}
