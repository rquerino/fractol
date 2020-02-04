/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:51:48 by rquerino          #+#    #+#             */
/*   Updated: 2020/02/04 15:00:28 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** Functions to get gradient colors according to the i value
** and between color_base and color_gradient.
*/

int		ft_getcolor(t_fract *f, int i)
{
	int	color;

	if (f->monochromatic == 1)
	{
		if (i == f->iterations)
			return (f->color_base);
		else
			return (f->color_base + i * 10);
	}
	else
	{
		color = i % f->iterations * (i < f->iterations);
		return ((color << 21) | (color << 10) | color);
	}
}

void	ft_reset_julia(t_fract *f)
{
	f->zoom = 1.0;
	f->move_x = 0;
	f->move_y = 0;
	f->iterations = 150;
	f->c_re = -0.7;
	f->c_im = 0.3;
	f->locked = 0;
	f->monochromatic = 0;
}

/*
** Quadratic Julia Sets
** 1) For every pixel: Znew = Zold^2 + C, radius = 2. The number of iterations
** is the color of the pixel.
** 2) The screen represents a part of the complex plano, inside the circle
** with radius 2 around the origin. For a pixel, x coord represents the real
** part of its complex coordinates, and y coord will be the imaginary part.
** 3) The value of the initial pixel you apply the function, Z can go to
** infinity or remain in the circle with radius 2.
** Those that remain are the ones that belong to the Julia set.
** Good link: https://lodev.org/cgtutor/juliamandelbrot.html
*/

int		ft_julia_calc(t_fract *f)
{
	int	i;

	i = 0;
	while (i < f->iterations)
	{
		f->o_re = f->n_re;
		f->o_im = f->n_im;
		f->n_re = f->o_re * f->o_re - f->o_im * f->o_im + f->c_re;
		f->n_im = 2 * f->o_re * f->o_im + f->c_im;
		if ((f->n_re * f->n_re + f->n_im * f->n_im) > 4)
			break ;
		i++;
	}
	return (i);
}

int		ft_draw_julia(t_fract *f)
{
	int	color;
	int	x;
	int	y;
	int	i;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			f->n_re = 1.5 * (x - WIDTH / 2) / (0.5 * f->zoom * WIDTH)
				+ f->move_x;
			f->n_im = (y - HEIGHT / 2) / (0.5 * f->zoom * HEIGHT) + f->move_y;
			i = ft_julia_calc(f);
			color = ft_getcolor(f, i);
			f->img[y * WIDTH + x] = color;
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img_ptr, 0, 0);
	return (1);
}
