/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:28:32 by user42            #+#    #+#             */
/*   Updated: 2022/02/26 16:46:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int	ft_prompt_pwd(void)
{
	
}*/

int	ft_builtin_pwd(char **argv)
{
	char	*buffer;

	if (argv[1])
		return (ft_custom_error("pwd: unavailable option"));
	buffer = getcwd(NULL, 0);
	if (!buffer)
		ft_putstr_fd("\n", 0);
	printf("%s\n", buffer);
	free(buffer);
	return (SUCCESS);
}