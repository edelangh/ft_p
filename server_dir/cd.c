/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/01 11:38:31 by edelangh          #+#    #+#             */
/*   Updated: 2015/02/01 16:24:32 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	lpwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_putendl(cwd);
	free(cwd);
}

void	lcd(char *src)
{
	if (chdir((src ? src : ".")) < 0)
		ft_putstr("\033[22;31mError : Can't open this file\033[22;37m\n");
}

char	*pwd(t_sock client)
{
	char	*cwd;
	char	*error;
	char	buf[1024];
	int		len;

	error = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_putstr_fd(cwd, client);
	else
	{
		error = "\033[22;31mError : An error occure on getting path\033[22;37m";
		ft_putstr_fd(".", client);
	}
	len = read(client, buf, 1023);
	buf[len] = '\0';
	ft_putstr(buf);
	return (error);
}

char	*cd(char *min_path, char *src)
{
	char	*error;

	if ((error = is_correct_path(min_path, src)))
		return (error);
	if (chdir(src) < 0)
		return ("\033[22;31mError : Can't open this file\033[22;37m\n");
	return (NULL);
}

int		is_dir(char *src)
{
	t_stat	s;
	int		fd;

	if ((fd = open(src, O_RDONLY)) < 0)
		return (0);
	fstat(fd, &s);
	close(fd);
	if (S_ISDIR(s.st_mode))
		return (1);
	else
		return (0);
}
