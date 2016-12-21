/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:40:11 by edelangh          #+#    #+#             */
/*   Updated: 2014/11/12 11:32:37 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	**lst;

	if (!alst || !del)
		return ;
	lst = alst;
	while (*lst)
	{
		alst = &((*lst)->next);
		ft_lstdelone(lst, del);
		lst = alst;
	}
}
