/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 12:38:36 by edelangh          #+#    #+#             */
/*   Updated: 2015/02/01 11:40:13 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	exevsock(t_sock server, char *cmd, char *s1)
{
	char	buf[1024];
	char	**tab;

	ft_sprintf(buf, "%s '%s'", cmd, s1);
	ft_putstr_fd(buf, server);
	tab = ft_splitcmd(buf);
	if (cmd_1(tab, server))
		if (cmd_2(tab, server))
			(void)1;
	buf[(read(server, buf, 1023))] = '\0';
	ft_freetab(tab);
}

char	*get_dir(t_sock server, char *src)
{
	char	**ls;
	int		i;

	exevsock(server, "lmkdir", src);
	exevsock(server, "cd", src);
	exevsock(server, "lcd", src);
	ls = get_dir_ls(server);
	i = -1;
	while (ls[++i])
	{
		if (i < 2)
			continue ;
		if (ft_strstr(ls[i], C_CYAN))
		{
			ls[i] = ft_strfreplace(ls[i], C_CYAN, "");
			ls[i] = ft_strfreplace(ls[i], C_EOC, "");
			get_dir(server, ls[i]);
		}
		else
			exevsock(server, "get", ls[i]);
	}
	lcd("..");
	exevsock(server, "cd", "..");
	return (NULL);
}

void	put_dir(t_sock server, char *src)
{
	DIR			*dir;
	t_dirent	*d;

	exevsock(server, "mkdir", src);
	exevsock(server, "cd", src);
	lcd(src);
	if ((dir = opendir(".")))
		while ((d = readdir(dir)))
		{
			if (d->d_type == DT_DIR)
			{
				if (ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, ".."))
					put_dir(server, d->d_name);
			}
			else
				exevsock(server, "put", d->d_name);
		}
	lcd("..");
	exevsock(server, "cd", "..");
	closedir(dir);
}

char	*getdir(t_sock server, char *src)
{
	char	buf[1024];

	read(server, buf, 1023);
	if (src)
	{
		ft_sprintf(buf, "getdir %s", src);
		get_dir(server, src);
	}
	else
		ft_sprintf(buf, "getdir");
	ft_putstr_fd(buf, server);
	return (NULL);
}

char	*putdir(t_sock server, char *src)
{
	char	buf[1024];

	read(server, buf, 1023);
	if (src)
	{
		ft_sprintf(buf, "putdir %s", src);
		put_dir(server, src);
	}
	else
		ft_sprintf(buf, "putdir");
	ft_putstr_fd(buf, server);
	return (NULL);
}
