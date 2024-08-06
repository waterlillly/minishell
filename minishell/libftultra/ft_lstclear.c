/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:20:39 by codespace         #+#    #+#             */
/*   Updated: 2024/08/06 18:31:35 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst || !del)
		return ;
	tmp = *lst;
	*lst = NULL;
	while (tmp)
	{
		tmp2 = tmp;
		(*del)(tmp2->content);
		tmp = tmp->next;
		free(tmp2);
	}
}
