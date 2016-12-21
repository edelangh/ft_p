/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 15:42:32 by edelangh          #+#    #+#             */
/*   Updated: 2015/02/02 14:45:34 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <sys/stat.h>
# include <dirent.h>

# define MAX_CLIENT_NBR 42
# define RECV_TS "Transferring start."
# define RECV_HEAD "Recv head\n"

typedef int					t_sock;
typedef struct protoent		t_protoent;
typedef struct sockaddr		t_sockaddr;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr_in6	t_sockaddr_in6;
typedef struct stat			t_stat;
typedef struct dirent		t_dirent;

typedef struct	s_head
{
	char		*name;
	size_t		lenght;
	size_t		package;
	int			type;
	size_t		start;
	int			fd;
}				t_head;

t_sock			create_server(int ip, char *proto_name);
t_sock			connect_server(char *ip, int port, char *proto_name);
char			*get_mkdir(char *src);
int				get_sock(t_sock server);
char			*receive(t_sock client, char *file, int is_server);
char			*put(t_sock server, char *file_src, int is_server);
char			*put_ls(t_sock client, char *min_path, char *src);
void			get_ls(t_sock server, char *src);
char			*cd(char *min_path, char *src);
char			*pwd(t_sock client);
void			lcd(char *src);
void			lls(char *src);
void			lpwd(void);
char			**get_dir_ls(t_sock server);
char			*is_correct_path(char *min_path, char *src);
int				is_dir(char *src);
void			init_put_header(t_head *head, char *src, int fd);
t_head			read_header(t_sock client);
void			head_to_a(t_sock server, t_head head);
#endif
