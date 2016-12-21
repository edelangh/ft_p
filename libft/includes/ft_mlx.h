/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 15:13:23 by edelangh          #+#    #+#             */
/*   Updated: 2015/01/23 17:45:24 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define MOTION_NOTIFY 6
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)
# define BUTTON_PRESS_MASK (1L<<2)
# define BUTTON_RELEASE_MASK (1L<<3)
# define MOTION_NOTIFY_MASK (1L<<6)

typedef unsigned int	t_uint;

typedef struct			s_p
{
	void				*mlx;
	void				*win;
}						t_p;

typedef struct			s_img
{
	void				*img;
	char				*data;
	unsigned int		*udata;
	int					width;
	int					height;
	int					endian;
	int					bpp;
	int					sizeline;
	int					sl_div;
	int					bpp_div;
}						t_img;

void					ft_fill_img(t_img *i, t_uint color);
void					ft_pixel_put_to_image(t_img *i, int x, int y, t_uint c);
t_img					*ft_new_img(void *mlx, int width, int height);
void					ft_draw_line(t_p *e, int *a, int *b, t_uint color);
t_img					*ft_load_img(void *mlx, char *src);
t_uint					ft_get_pixel_from_image(t_img *i, int x, int y);
void					ft_resize_img(t_img *to, t_img *i, int *pos, int *size);
int						ft_destroy_img(void *mlx, t_img *i);
#endif
