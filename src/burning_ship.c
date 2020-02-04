/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:22:50 by rquerino          #+#    #+#             */
/*   Updated: 2020/02/04 14:59:38 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdlib.h>

void	ft_reset_burning(t_fract *f)
{
	f->zoom = 1.0;
	f->move_x = 0;
	f->move_y = 0;
	f->iterations = 200;
	f->monochromatic = 0;
}

/*
** Burning Ship Sets
*/

int		ft_burning_calc(t_fract *f)
{
	int i;

	i = 0;
	while (i < f->iterations)
	{
		f->o_re = f->n_re;
		f->o_im = f->n_im;
		f->n_re = fabs(f->o_re * f->o_re - f->o_im * f->o_im + f->x);
		f->n_im = fabs(2 * f->o_re * f->o_im + f->y);
		if ((f->n_re * f->n_re + f->n_im * f->n_im) > 4)
			break ;
		i++;
	}
	return (i);
}

int		ft_draw_burning(t_fract *f)
{
	unsigned long	color;
	int				x;
	int				y;
	int				i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			f->x = 1.5 * (x - WIDTH / 2) / (0.5 * f->zoom * WIDTH) + f->move_x;
			f->n_re = f->x;
			f->y = (y - HEIGHT / 2) / (0.5 * f->zoom * HEIGHT) + f->move_y;
			f->n_im = f->y;
			i = ft_burning_calc(f);
			color = ft_getcolor(f, i);
			f->img[y * WIDTH + x] = color;
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img_ptr, 0, 0);
	return (1);
}
