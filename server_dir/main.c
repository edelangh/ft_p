/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 15:32:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/12/21 18:01:13 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cmd1(char **tab, t_sock client, char **error, char *server_pwd)
{
	if (!ft_strcmp(tab[0], "put"))
		*error = (!tab[1] || !ft_strlen(tab[1])
				? "\033[22;31mError : usage :put <file>\033[22;37m"
				: receive(client, tab[1], 1));
	else if (!ft_strcmp(tab[0], "get"))
	{
		*error = (!tab[1] || !ft_strlen(tab[1])
				? "\033[22;31mError : usage : put <file>\033[22;37m"
				: put(client, tab[1], 1));
	}
	else if (!ft_strcmp(tab[0], "pwd"))
		*error = pwd(client);
	else if (!ft_strcmp(tab[0], "ls"))
		*error = put_ls(client, server_pwd, tab[1]);
	else if (!ft_strcmp(tab[0], "cd"))
		*error = cd(server_pwd, tab[1]);
	else if (!ft_strcmp(tab[0], "lls") || !ft_strcmp(tab[0], "lcd")
			|| !ft_strcmp(tab[0], "lpwd"))
		(void)tab;
	else if (!ft_strcmp(tab[0], "lmkdir"))
		*error = (tab[1] ? *error
				: "\033[22;31mError : usage : lmkdir <dir>\033[22;37m");
	else
		return (1);
	return (0);
}

int		cmd2(char **tab, t_sock client, char **error)
{
	(void)client;
	if (!ft_strcmp(tab[0], "mkdir"))
		*error = get_mkdir(tab[1]);
	else if (!ft_strcmp(tab[0], "getdir"))
		*error = (tab[1] ? *error
				: "\033[22;31mError : usage : getdir <dir>\033[22;37m");
	else if (!ft_strcmp(tab[0], "putdir"))
		*error = (tab[1] ? *error
				: "\033[22;31mError : usage : putdir <dir>\033[22;37m");
	else if (!ft_strcmp(tab[0], "lrm"))
		*error = (tab[1] ? *error
				: "\033[22;31mError : usage : lrm <file|dir>\033[22;37m");
	else if (!ft_strcmp(tab[0], "rm"))
	{
		if (!tab[1])
			*error = "\033[22;31mError : usage : rm <file|dir>\033[22;37m";
		else
		{
			if (ft_rm(tab[1]) == -1)
				*error = "\033[22;31mError : can't rm it\033[22;37m";
		}
	}
	else
		return (1);
	return (0);
}

void	on_client(t_sock client, t_sockaddr_in sin, int addr_len)
{
	char	buf[1024];
	size_t	len;
	char	**tab;
	char	*error;
	char	*server_pwd;

	(void)sin;
	(void)addr_len;
	server_pwd = getcwd(NULL, 0);
	while ((len = recv(client, buf, sizeof(buf) - 1, 0)) > 0)
	{
		error = NULL;
		buf[len] = '\0';
		dprintf(1, "'%s'\n", buf);
		dprintf(1, "client %d : '%s'\n", client, buf);
		tab = ft_splitcmd(buf);
		if (cmd1(tab, client, &error, server_pwd))
			if (cmd2(tab, client, &error))
				error = ft_strjoin(
						"\033[22;31mError : Cmd not found :\033[22;37m", buf);
		ft_putstr_fd((error && ft_strlen(error) ? (error)
					: "\033[22;32mSuccess\033[22;37m"), client);
	}
	ft_dprintf(1, "{yellow}client %d deconnection.\033[22;37m\n", client);
	close(client);
	exit(1);
}

void	run_server(t_sock server, void (*f)(t_sock, t_sockaddr_in, int))
{
	t_sock			client;
	t_sockaddr_in	sin;
	int				addr_len;

	while (1)
	{
		ft_dprintf(1, "{yellow}waiting client ...\033[22;37m\n");
		client = accept(server, (t_sockaddr*)&sin, (socklen_t*)&addr_len);
		ft_dprintf(1, "{yellow}new client : %d\033[22;37m\n", client);
		if ((fork()) == 0)
			f(client, sin, addr_len);
	}
}

int		main(int ac, char **av)
{
	t_sock	server;

	if (ac < 2)
		exit(ft_dprintf(1, "\033[22;31mUsage %s [PORT]\033[22;37m\n", av[0]));
	server = create_server(ft_atoi(av[1]), "tcp");
	ft_dprintf(1, "serveur socket : %d\n", (int)server);
	run_server(server, &on_client);
	return (0);
}
