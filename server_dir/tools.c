/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 11:39:17 by edelangh          #+#    #+#             */
/*   Updated: 2015/02/02 15:30:36 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		get_sock(t_sock server)
{
	char	buf[1024];
	int		len;

	len = read(server, buf, 1023);
	buf[len] = '\0';
	ft_printf(buf);
	write(1, "\n", 1);
	return (0);
}

void	init_put_header(t_head *head, char *src, int fd)
{
	t_stat	s;
	char	**tab;

	tab = ft_strsplit(src, '/');
	src = tab[ft_tablen((void**)tab) - 1];
	fstat(fd, &s);
	head->name = ft_strdup(src);
	head->lenght = s.st_size;
	head->package = 0;
	head->type = 1;
	ft_freetab(tab);
}

char	*is_correct_path(char *min_path, char *src)
{
	char	*new_cwd;
	char	*old_cwd;

	old_cwd = getcwd(NULL, 0);
	if (chdir(src) < 0)
		return ("\033[22;31mError : Can't open this dir\033[22;37m");
	new_cwd = getcwd(NULL, 0);
	if (!ft_strstr(new_cwd, min_path))
	{
		chdir(old_cwd);
		free(new_cwd);
		free(old_cwd);
		return ("\033[22;31mError : You dont have correct right\033[22;37m");
	}
	chdir(old_cwd);
	free(new_cwd);
	free(old_cwd);
	return (NULL);
}

t_head	read_header(t_sock client)
{
	char	buf[1024];
	char	**tab;
	int		len;
	t_head	head;

	len = read(client, buf, 1023);
	ft_putstr_fd(RECV_HEAD, client);
	buf[len] = '\0';
	tab = ft_strsplit(buf, '/');
	head.start = 0;
	if (tab)
	{
		head.type = ft_atoi(tab[0]);
		head.name = tab[1];
		if (head.type != 2)
			head.fd = open(head.name, O_RDWR | O_TRUNC | O_CREAT, 0777);
		head.lenght = (size_t)ft_atoi(tab[2]);
		ft_freetab(tab);
	}
	return (head);
}

void	head_to_a(t_sock server, t_head head)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strfjoin(tmp, ft_itoa(head.type), 0, 1);
	tmp = ft_strfjoin(tmp, "/", 1, 0);
	tmp = ft_strfjoin(tmp, head.name, 1, 0);
	tmp = ft_strfjoin(tmp, "/", 1, 0);
	tmp = ft_strfjoin(tmp, ft_zutoa(head.lenght), 1, 1);
	tmp = ft_strfjoin(tmp, "/", 1, 0);
	if (tmp)
	{
		write(server, tmp, ft_strlen(tmp));
		free(tmp);
	}
}
