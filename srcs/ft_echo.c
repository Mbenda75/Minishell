/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:01:53 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/18 11:27:09 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option(char *str)
{
	int	i;
  
	i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] != '-'))
			return (0);
		if (i > 0 && (str[i] != 'n'))
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

int	ft_len(char *cmd[])
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	ft_echo_dollar(char	**cmd, int i, int j)
{
	t_env	*echo_env;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		size;

	echo_env = g_list;
	size = ft_strlen(cmd[i]);
	tmp = ft_substr(cmd[i], j, size - 1);
	tmp3 = tmp;
	tmp = ft_strjoin(tmp, "=");
	free(tmp3);
	while (echo_env)
	{
		if (ft_strncmp(echo_env->content, tmp, ft_strlen(tmp)) == SUCCESS)
		{
			tmp2 = ft_substr(echo_env->content,
			ft_find_where_is_equal(echo_env->content) + 1,
			ft_strlen(echo_env->content));
			ft_putstr_fd(tmp2, 1);
			if (cmd[i + 1])
				write(1, " ", 1);
			free(tmp2);
			break ;
		}
		echo_env = echo_env->next;
	}
	free(tmp);
}

int	ft_built_echo(char *cmd[])
{
	t_decompte	m;
	char		*tmp;

	m.i = 1;
	m.l = 0;
	m.j = 0;
	if (ft_len(cmd) != 1)
	{
		while (cmd[m.i] && check_option(cmd[m.i]))
		{
			m.l = 1;
			m.i++;
		}
		while (cmd[m.i])
		{
			m.j = 0;
			while (cmd[m.i][m.j])
			{
				if (cmd[m.i][m.j] == '$')
				{
					m.j++;
					ft_echo_dollar(cmd, m.i, m.j);
					break ;
				}
				else
				{
					ft_putstr_fd(cmd[m.i], 1);
					if (cmd[m.i + 1])
						write(1, " ", 1);
					break ;
				}
			m.j++;
			}
		m.i++;
		}
	}
	if (!m.l)
		write(1, "\n", 1);
	return (0);
}
