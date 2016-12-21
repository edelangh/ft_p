/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/01 11:39:02 by edelangh          #+#    #+#             */
/*   Updated: 2015/02/01 16:26:03 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	lls(char *src)
{
	DIR			*dir;
	t_dirent	*dirent;
	char		*ls_str;
	char		*tmp;

	ls_str = NULL;
	if (!(dir = opendir((src ? src : "."))))
	{
		ft_putstr("\033[22;31mError : Can't open this dir\033[22;37m");
		return ;
	}
	while ((dirent = readdir(dir)))
	{
		tmp = ls_str;
		if (dirent->d_type == DT_DIR)
			ft_asprintf(&ls_str, "%s{cyan}%s\033[22;37m\n", ls_str,
					dirent->d_name);
		else
			ft_asprintf(&ls_str, "%s%s\n", ls_str, dirent->d_name);
		if (tmp)
			free(tmp);
	}
	ft_putstr(ls_str);
	free(ls_str);
}

void	put_ls2(DIR *dir, char *ls_str, t_sock client)
{
	char		*tmp;
	char		buf[1024];
	t_dirent	*dirent;

	while ((dirent = readdir(dir)))
	{
		if (tmp = ls_str, dirent->d_type == DT_DIR)
			ft_asprintf(&ls_str, "%s{cyan}%s\033[22;37m\n", ls_str,
					dirent->d_name);
		else
			ft_asprintf(&ls_str, "%s%s\n", ls_str, dirent->d_name);
		ft_memdel((void**)&tmp);
	}
	ft_putstr_fd(ls_str, client);
	read(client, buf, 1023);
	free(ls_str);
}

char	*put_ls(t_sock client, char *min_path, char *src)
{
	DIR			*dir;
	char		*ls_str;
	char		buf[1024];

	if ((ls_str = is_correct_path(min_path, (src ? src : "."))))
	{
		ft_putstr_fd("(empty)\n", client);
		read(client, buf, 1023);
		return (ls_str);
	}
	if (!(dir = opendir((src ? src : "."))))
		return ("\033[22;31mError : Can't open this dir\033[22;37m");
	put_ls2(dir, ls_str, client);
	return (NULL);
}

void	get_ls(t_sock server, char *src)
{
	char	buf[1024];
	size_t	len;

	ft_dprintf(1, "%s :\n", (src ? src : "."));
	while ((len = read(server, buf, 1023)) > 0)
	{
		buf[len] = '\0';
		ft_putstr(buf);
		if (len != 1023)
			break ;
	}
	ft_putstr_fd("GET_LS:EOT\n", server);
}

char	**get_dir_ls(t_sock server)
{
	char	buf[1024];
	int		len;
	char	*res;
	char	**tab;

	res = NULL;
	write(server, "ls", 2);
	while ((len = read(server, buf, 1023)) > 0)
	{
		buf[len] = '\0';
		res = ft_strfjoin(res, buf, 1, 0);
		if (len != 1023)
			break ;
	}
	ft_putstr_fd("GET_DIR_LS:EOT\n", server);
	read(server, buf, 1023);
	tab = ft_strsplit(res, '\n');
	free(res);
	return (tab);
}
