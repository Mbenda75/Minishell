/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:51:40 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/17 13:47:55 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_the_equal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str[j])
	{
		if (str[i - 1] == '=' && str[j] == '=')
			return (0);
		j++;
	}
	if (str[i - 1] == '=')
		return (2);
	i = 0;
	while (str[i])
	{
		if (str[0] == '=')
			return (FAILURE);
		if (str[i] == '=' && i != 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	ft_find_where_is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_trim_name(char *cmd)
{
	char	*tmp;
	
	tmp = ft_strtrim(cmd, "+");
	return (tmp);
}

char *ft_add_env_var(char *after_equal)
{
	t_env *verify;
	t_env *env_value;
	char *new_after_equal;
	char *tmp2;

	verify = g_list;
	env_value = g_list;
	tmp2 = ft_strtrim(after_equal, "$");
	tmp2 = ft_strjoin(tmp2, "=");
	printf("%s\n", tmp2);
	while (verify) 
	{
		if (ft_strncmp(verify->content, tmp2, ft_strlen(tmp2)) == SUCCESS)
			break ;
				verify = verify->next;
		if (verify == NULL)
			return (after_equal);
	}
	while (env_value)
	{
		if (ft_strncmp(env_value->content, tmp2, ft_strlen(tmp2)) == SUCCESS)
		{
			tmp2 = ft_substr(env_value->content, ft_find_where_is_equal(env_value->content) + 1, ft_strlen(env_value->content));	
			new_after_equal = tmp2;
			break ;
		}
		env_value = env_value->next;
	}
	return (new_after_equal); 
}

char *ft_add_content(char *avant_equal, char *after_equal)
{
	t_env *export_content;
	t_env *verify;
	char *new_after_equal;
	char *tmp;
	char *tmp2;

	verify = g_list; //liste qui va verifier l'existence de la var
	export_content = g_list; // va nous servir a ajouter la var
	tmp = ft_strjoin(avant_equal, "=");
	while (verify) /// je verifie si la variable existe deja pour eviter un segfault
	{
		if (ft_strncmp(verify->content, tmp, ft_strlen(tmp)) == SUCCESS)
			break ; //si elle existe je sors de la boucle
				verify = verify->next;
		if (verify == NULL) //si elle n'existe pas je renvoit after_equal pour eviter segfault
			return (after_equal);
	}
	while (export_content) // je rajoute le content dans la variable 
	{
		if (ft_strncmp(export_content->content, tmp, ft_strlen(tmp)) == SUCCESS)
		{
			tmp2 = ft_substr(export_content->content, ft_find_where_is_equal(export_content->content) + 1, ft_strlen(export_content->content));			
			new_after_equal = ft_strjoin(tmp2, after_equal); //je prend la contenu de la var apres le = et je le join
			break ;
		}
		export_content = export_content->next;
	}
	return (new_after_equal);
}

int	ft_check_variable_after_equal(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (!((cmd[i] >= 'a' && cmd[i] <= 'z' )
				|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
				|| (cmd[i] >= '0' && cmd[i] <= '9')
				|| (cmd[i] == '_' || cmd[i] == '=')
				|| (cmd[i] == '+' || cmd[i] == '*')
				|| (cmd[i] == '-' || cmd[i] == '.')
				|| (cmd[i] == '$' || cmd[i] == '^')
				|| (cmd[i] == '?' || cmd[i] == ',')
				|| (cmd[i] == '-' || cmd[i] == '{')
				|| (cmd[i] == '}' || cmd[i] == '[')
				|| (cmd[i] == ']' || cmd[i] == '#')
				|| (cmd[i] == '~' || cmd[i] == '/')
				|| (cmd[i] == '@' || cmd[i] == '%')
				|| (cmd[i] == '\'' || cmd[i] == '"')))
			return (ft_custom_error("export: not valid identifier1"));
		i++;
	}
	return (0);
}

int	ft_check_variable_before_equal(char *cmd)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while(cmd[j])
		j++;
	if (cmd[j - 1] == '$')
		return (ft_custom_error("export: not valid identifier"));
	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (ft_custom_error("export: not valid identifier2"));
	while (cmd[i])
	{
		if (!((cmd[i] >= 'a' && cmd[i] <= 'z' )
				|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
				|| (cmd[i] >= '0' && cmd[i] <= '9')
				|| (cmd[i] == '_' || cmd[i] == '=')
				|| (cmd[i] == '$' || (cmd[j - 1] == '+' && cmd[j - 2] != '+'))))
			return (ft_custom_error("export: not valid identifier3"));
		i++;
	}
	return (0);
}
