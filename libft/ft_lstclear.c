/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:19:50 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/31 16:32:30 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*sup;

	if (!del || !lst || !*lst)
		return ;
	while (*lst && lst)
	{
		sup = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = sup;
	}
}
