/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 17:09:41 by edelangh          #+#    #+#             */
/*   Updated: 2015/01/12 18:34:01 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tablen(void **tab)
{
	size_t	len;

	len = 0;
	if (!tab)
		return (0);
	while (tab[len])
		++len;
	return (len);
}
