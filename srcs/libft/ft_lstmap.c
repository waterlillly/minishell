/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:36:10 by codespace         #+#    #+#             */
/*   Updated: 2023/09/18 18:26:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*out;

	if (!lst || !f)
		return (NULL);
	out = NULL;
	while (lst)
	{
		tmp = ft_lstnew(NULL);
		if (!tmp)
		{
			ft_lstclear(&out, del);
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		tmp->content = (*f)(lst->content);
		ft_lstadd_back(&out, tmp);
		lst = lst->next;
	}
	return (out);
}
