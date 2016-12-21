/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 12:39:15 by edelangh          #+#    #+#             */
/*   Updated: 2015/02/01 11:45:10 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "ft_p.h"

int		cmd_1(char **tab, t_sock server);
int		cmd_2(char **tab, t_sock server);
char	*getdir(t_sock server, char *src);
char	*putdir(t_sock server, char *src);
#endif
