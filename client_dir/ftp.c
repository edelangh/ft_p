/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/01 11:37:03 by edelangh          #+#    #+#             */
/*   Updated: 2015/02/02 15:42:10 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	load_skin(size_t writed, size_t lenght)
{
	double	ratio;
	double	i;
	char	*tmp;

	tmp = NULL;
	ratio = ((double)writed / lenght) * 80;
	i = 0;
	while (++i <= 100.0)
		tmp = ft_strfjoin(tmp, "\b \b", 1, 0);
	tmp = ft_strfjoin(tmp, "[", 1, 0);
	i = 0;
	while (++i < ratio)
		tmp = ft_strfjoin(tmp, "=", 1, 0);
	while (++i <= 80.0)
		tmp = ft_strfjoin(tmp, " ", 1, 0);
	tmp = ft_strfjoin(tmp, "]", 1, 0);
	ft_dprintf(1, "%s%5.1f%", tmp, (ratio * 100) / 80);
	free(tmp);
	if (writed == lenght)
		write(1, "\n", 1);
}

char	*get_mkdir(char *src)
{
	t_stat		s;

	if (!src)
		return ("\033[22;31mError : mkdir [FILE]\033[22;37m\n");
	if (lstat(src, &s) == -1)
	{
		if (mkdir(src, 0777) == -1)
			return ("\033[22;31mError : can't create this dir\033[22;37m");
	}
	else
		return ("\033[22;31mError : file already exit ?\033[22;37m");
	return (NULL);
}

char	*receive(t_sock client, char *file, int is_server)
{
	size_t	writed;
	char	buf[1000001];
	t_head	head;
	size_t	len;
	char	*error;

	(void)file;
	error = NULL;
	(is_server ? ft_putstr_fd(RECV_TS, client) : 0);
	head = read_header(client);
	writed = head.start;
	if (head.type == 2)
		error = "\033[22;31mError can't open this file\033[22;37m";
	while (writed < head.lenght && (len = read(client, buf, 1000000)) > 0)
	{
		buf[len] = '\0';
		writed += len;
		write(head.fd, buf, len);
		load_skin(writed, head.lenght);
	}
	if (head.fd > 0)
		close(head.fd);
	(is_server ? 0 : ft_dprintf(client, "Transferring end."));
	return (error);
}

int		put_2(t_sock server, t_head head, int fd, int is_server)
{
	size_t	writed;
	char	buf[1000001];
	size_t	len;

	head_to_a(server, head);
	read(server, buf, ft_strlen(RECV_HEAD));
	writed = 0;
	if (head.type == 1)
		while ((len = read(fd, buf, 1000000)) > 0)
		{
			writed += len;
			buf[len] = '\0';
			write(server, buf, len);
			load_skin(writed, head.lenght);
		}
	ft_putchar('\n');
	close(fd);
	(is_server ? get_sock(server) : 0);
	free(head.name);
	return (0);
}

char	*put(t_sock server, char *src, int is_server)
{
	int		fd;
	t_head	head;

	(is_server ? 0 : get_sock(server));
	fd = open(src, O_RDONLY);
	init_put_header(&head, src, fd);
	if (fd < 0 || is_dir(src))
	{
		head.lenght = 0;
		head.type = 2;
		ft_dprintf(1, "\033[22;31mCan't open '%s'\033[22;37m\n", src);
		put_2(server, head, fd, is_server);
		return ("\033[22;31mCan't open this file\033[22;37m");
	}
	put_2(server, head, fd, is_server);
	return (NULL);
}
