/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:40:02 by user42            #+#    #+#             */
/*   Updated: 2022/03/04 17:36:40 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**realloc_envs(size_t size, char **envp)
{
	char	**new;
	size_t	i;

	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (envp[i] && i < size)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[size] = 0;
	//ft_free_charr(envp);
	return (new);
}

unsigned int
	str_chr(const char *s, char c)
{
	const char	*t;

	t = s;
	while (1)
	{
		if (!*t || *t == c)
			break ;
		t++;
		if (!*t || *t == c)
			break ;
		t++;
		if (!*t || *t == c)
			break ;
		t++;
		if (!*t || *t == c)
			break ;
		t++;
	}
	return (t - s);
}

unsigned int
	str_len(const char *s)
{
	register const char	*t;

	t = s;
	while (1)
	{
		if (!*t)
			return (t - s);
		t++;
		if (!*t)
			return (t - s);
		t++;
		if (!*t)
			return (t - s);
		t++;
		if (!*t)
			return (t - s);
		t++;
	}
}

static int
	ft_built_in_export_check(char *s)
{
	char			*p;

	p = s;
	while (*p)
	{
		if (!((*p >= 'a' && *p <= 'z')
				|| (*p >= 'A' && *p <= 'Z')
				|| (*p >= '0' && *p <= '9')
				|| (*p == '_')))
			return (ft_custom_error("export: not valid identifier"));
		p++;
	}
	return (SUCCESS);
}

char **ft_env_cpy(char **envp, char **envp_2)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	envp_2 = (char **)malloc(sizeof(char *) * (i));
	if (!envp_2)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_2[i] = envp[i];
		i++;
	}
	return (envp_2);	
}


static int
	ft_built_in_export_add(char *s, char *t, char **envp)
{
	char			*c;
	int				i;
	static int		k;
	static int		j;

	i = 0;
	if (ft_built_in_export_check(s))
		return (FAILURE);
	c = ft_strjoin(s, "=");
	c = ft_strjoin(c, t);
	while (envp[i])
		i++;
	j = i;
/* 	for (int i = 0; g_list->split_byspace[i];i++)
	printf("split by pipe== %s\n", g_list->split_byspace[i]);  */
	if (k == 0)
		g_list->env_2 = ft_env_cpy(envp, g_list->env_2);
/*	g_list->env_2 = realloc_envs(k + j, g_list->env_2);
	g_list->env_2[k + j] = c;*/
	printf("k avant = %d\n", k);
	if (g_list->unset_minus > 0)
	{
		while (g_list->unset_minus >= 0)
		{
			g_list->unset_minus--;
			k--;
		}
	}
	g_list->env_2 = realloc_envs(k + j, g_list->env_2);
	g_list->env_2[k + j] = c;
	if (k > 0)
		k++;
	if (k == 0)
		k++;
	g_list->unset_minus = 0;
	printf("k après = %d\n", k);
	printf("unset_minus EXPORT = %d\n", g_list->unset_minus);
	free(c);
	return (SUCCESS);
}



int ft_built_in_export(char **cmd, char **envp)
{
    unsigned int chr;
    char        tmp;
    char        *s;
    
    if (cmd[1] == NULL)
        ft_built_in_env(cmd, envp);
	else
    {
        s = cmd[1];
		chr = str_chr(s, '=');
		if (chr == str_len(s))
			ft_built_in_export_add(s, "", envp);
		else
		{
			tmp = s[chr];
			s[chr] = 0;
			ft_built_in_export_add(s, s + chr + 1, envp);
			s[chr] = tmp;
		}
    }
    return (SUCCESS);
}