/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 15:32:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 17:49:55 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_sock	connect_server(char *ip, int port, char *proto_name)
{
	t_sock			client;
	t_protoent		*proto;
	t_sockaddr_in	sin;

	proto = getprotobyname(proto_name);
	if (proto)
	{
		if ((client = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		{
			perror("connect_server :");
			exit(1);
		}
	}
	else
	{
		client = 0;
		exit(2);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(ip);
	if ((connect(client, (const t_sockaddr*)&sin, sizeof(sin))) == -1)
		exit(ft_dprintf(1, "\033[22;31mError : init client on %d\033[22;37m\n",
						port));
	return (client);
}

int		cmd_1(char **tab, t_sock server)
{
	if (!ft_strcmp(tab[0], "quit"))
		exit(ft_dprintf(1, "\033[22;32mGood bye !\033[22;37m\n"));
	else if (!ft_strcmp(tab[0], "pwd"))
	{
		get_sock(server);
		ft_putstr_fd("PWD:EOT\n", server);
	}
	else if (!ft_strcmp(tab[0], "put") && tab[1] && ft_strlen(tab[1]))
	{
		put(server, tab[1], 0);
	}
	else if (!ft_strcmp(tab[0], "get") && tab[1] && ft_strlen(tab[1]))
	{
		receive(server, tab[1], 0);
	}
	else
		return (1);
	return (0);
}

int		cmd_2(char **tab, t_sock server)
{
	if (!ft_strcmp(tab[0], "ls"))
		get_ls(server, tab[1]);
	else if (!ft_strcmp(tab[0], "lls"))
		lls(tab[1]);
	else if (!ft_strcmp(tab[0], "lcd"))
		lcd(tab[1]);
	else if (!ft_strcmp(tab[0], "lpwd"))
		lpwd();
	else if (!ft_strcmp(tab[0], "mkdir"))
		(void)1;
	else if (!ft_strcmp(tab[0], "lmkdir"))
		get_mkdir(tab[1]);
	else if (!ft_strcmp(tab[0], "getdir"))
		getdir(server, tab[1]);
	else if (!ft_strcmp(tab[0], "putdir"))
		putdir(server, tab[1]);
	else if (!ft_strcmp(tab[0], "lrm") && tab[1])
		ft_rm(tab[1]);
	else if (!ft_strcmp(tab[0], "rm"))
		(void)1;
	else
		return (1);
	return (0);
}

int		main(int ac, char **av)
{
	t_sock	server;
	char	*line;
	char	**tab;

	if (ac < 2)
		exit(ft_dprintf(1, "\033[22;31mUsage %s [SERVER] [PORT]\033[22;37m\n",
					av[0]));
	server = connect_server(av[1], ft_atoi(av[2]), "tcp");
	ft_dprintf(1, "{yellow}serveur : %d\033[22;37m\n", (int)server);
	while (ft_putstr("\n?> "), get_next_line(0, &line) == 1)
	{
		tab = ft_splitcmd(line);
		if (!tab || !tab[0])
			continue ;
		write(server, line, ft_strlen(line));
		if (cmd_1(tab, server))
			if (cmd_2(tab, server))
				(void)2;
		ft_memdel((void**)&line);
		ft_freetab(tab);
		get_sock(server);
	}
	return (0);
}
