/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:58:16 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/30 17:06:19 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fractol.h"

void    ft_reset_tricorn(t_fract *f) {
	// mouse scroll
	f->zoom = 1.0;
	// keyboard keys WASD
	f->moveX = 0;
	f->moveY = 0;
	// +/- keyboard
	f->iterations = 200;
	f->locked = 0;
}

/*
** tricorn Sets
** Good link: http://en.wikipedia.org/wiki/Tricorn_%28mathematics%29
** Good link: https://www.hindawi.com/journals/jfs/2015/417167/
*/

int		ft_tricorn_calc(t_fract *f) {
	int	i;

	i = 0;
	while (i < f->iterations) {
		f->oldRe = f->newRe;
		f->oldIm = f->newIm;
		f->newRe = f->oldRe * f->oldRe - f->oldIm * f->oldIm + f->x;
		f->newIm = -2 * f->oldRe * f->oldIm + f->y;
		if((f->newRe * f->newRe + f->newIm * f->newIm) > 4) break;
		i++;
	}
	return (i);
}

int		ft_draw_tricorn(t_fract *f) {
	unsigned long   color;
	int				x;
	int				y;
	int				i;

	y = -1;
	while (++y < HEIGHT) {
		x = -1;
		while (++x < WIDTH) {
			f->x = 1.5 * (x - WIDTH / 2) / (0.5 * f->zoom * WIDTH) + f->moveX;
			f->newRe = f->x;
			f->y = (y - HEIGHT / 2) / (0.5 * f->zoom * HEIGHT) + f->moveY;
			f->newIm = f->y;
			i = ft_tricorn_calc(f);
			f->color->r = i % f->iterations * (i < f->iterations);
			f->color->g = i % f->iterations * (i < f->iterations);
			f->color->b = i % f->iterations * (i < f->iterations);
			
			color = ((f->color->r << 16) | (f->color->g << 8) | f->color->b);
			// color = ((((f->color->R >> 16) & 0xFF) << 16) | (((f->color->G >> 8) & 0xFF) << 8) | (f->color->B & 0xff));
			f->img[y * WIDTH + x] = color;
			// f->img[y * WIDTH + x] = (i << 21) + (i << 10) + i * 8;
		}
		mlx_put_image_to_window(f->mlx, f->win, f->img_ptr, 0, 0);
	}
	return (1);
}