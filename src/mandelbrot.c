/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:16:35 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/30 20:34:47 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_reset_mandelbrot(t_fract *f)
{
	f->zoom = 1.0;
	f->move_x = -0.5;
	f->move_y = 0;
	f->iterations = 150;
	f->monochromatic = 0;
}

/*
** Mandelbrot set
** 1) The mandelbrot set represents every complex point c for which the
** Julia Set will be connected, or every Julia Set that contains the origin.
** Good link: https://lodev.org/cgtutor/juliamandelbrot.html
*/

int		ft_mandelbrot_calc(t_fract *f)
{
	int	i;

	i = 0;
	while (i < f->iterations)
	{
		f->o_re = f->n_re;
		f->o_im = f->n_im;
		f->n_re = f->o_re * f->o_re - f->o_im * f->o_im + f->pr;
		f->n_im = 2 * f->o_re * f->o_im + f->pi;
		if ((f->n_re * f->n_re + f->n_im * f->n_im) > 4)
			break ;
		i++;
	}
	return (i);
}

int		ft_draw_mandelbrot(t_fract *f)
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
			f->pr = 1.5 * (x - WIDTH / 2) / (0.5 * f->zoom * WIDTH)
				+ f->move_x;
			f->pi = (y - WIDTH / 2) / (0.5 * f->zoom * HEIGHT) + f->move_y;
			f->o_re = 0;
			f->n_re = 0;
			f->o_im = 0;
			f->n_im = 0;
			i = ft_mandelbrot_calc(f);
			color = ft_getcolor(f, i);
			f->img[y * WIDTH + x] = color;
		}
		mlx_put_image_to_window(f->mlx, f->win, f->img_ptr, 0, 0);
	}
	return (1);
}
