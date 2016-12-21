/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:37:41 by edelangh          #+#    #+#             */
/*   Updated: 2014/11/10 11:37:00 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s1;

	s1 = (char*)s;
	while (*s1)
	{
		if ((*s1) == (char)c)
			return (s1);
		++s1;
	}
	if ((*s1) == (char)c)
		return (s1);
	return (NULL);
}
