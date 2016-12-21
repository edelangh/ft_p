/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/01 16:32:48 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 17:48:11 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

t_sock	create_server(int port, char *proto_name)
{
	t_sock			server;
	t_protoent		*proto;
	t_sockaddr_in	sin;

	proto = getprotobyname(proto_name);
	if (proto)
	{
		if ((server = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		{
			perror("create_server :");
			exit(1);
		}
	}
	else
	{
		server = 0;
		exit(1);
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(server, (const t_sockaddr*)&sin, sizeof(sin))) == -1)
		exit(ft_dprintf(1, "{red}Error initialize server on %d{eoc}\n", port));
	listen(server, MAX_CLIENT_NBR);
	return (server);
}
