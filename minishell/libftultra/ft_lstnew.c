/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:27:29 by codespace         #+#    #+#             */
/*   Updated: 2024/08/06 18:33:12 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*out;

	out = (t_list *)malloc(sizeof(*out));
	if (!out)
		return (out);
	out->content = content;
	out->next = NULL;
	return (out);
}
