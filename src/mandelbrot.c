/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:16:35 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/29 16:22:33 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fractol.h"

void    ft_reset_mandelbrot(t_fract *f) {
	// mouse scroll
	f->zoom = 1.0;
	// keyboard keys WASD
	f->moveX = -0.5;
	f->moveY = 0;
	// +/- keyboard
	f->iterations = 150;
}

/*
** Mandelbrot set
** 1) The mandelbrot set represents every complex point c for which the Julia Set will be connected, or
** every Julia Set that contains the origin.
** Good link: https://lodev.org/cgtutor/juliamandelbrot.html
*/

int	ft_mandelbrot_calc(t_fract *f) {
	int	i;

	i = 0;
	while (i < f->iterations) {
		//remember value of previous iteration
		f->oldRe = f->newRe;
		f->oldIm = f->newIm;
		//the actual iteration, the real and imaginary part are calculated
		f->newRe = f->oldRe * f->oldRe - f->oldIm * f->oldIm + f->pr;
		f->newIm = 2 * f->oldRe * f->oldIm + f->pi;
		//if the point is outside the circle with radius 2: stop
		if((f->newRe * f->newRe + f->newIm * f->newIm) > 4) break;
		i++;
	}
	return (i);
}

int	ft_draw_mandelbrot(t_fract *f) {
	unsigned long   color;
	int				x;
	int				y;
	int				i;

	y = -1;
	while (++y < HEIGHT) {
		x = -1;
		while (++x < WIDTH) {
			//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
			f->pr = 1.5 * (x - WIDTH / 2) / (0.5 * f->zoom * WIDTH) + f->moveX;
			f->pi = (y - WIDTH / 2) / (0.5 * f->zoom * HEIGHT) + f->moveY;
			f->oldRe = 0;
			f->newRe = 0;
			f->oldIm = 0;
			f->newIm = 0;
			i = ft_mandelbrot_calc(f);
			// Maybe a color function here
			f->color->r = i % f->iterations * (i < f->iterations);
			f->color->g = i % f->iterations * (i < f->iterations);
			f->color->b = i % f->iterations * (i < f->iterations);
			
			color = ((f->color->r << 21) | (f->color->g << 10) | f->color->b);
			// color = ((((f->color->R >> 16) & 0xFF) << 16) | (((f->color->G >> 8) & 0xFF) << 8) | (f->color->B & 0xff));
			f->img[y * WIDTH + x] = color;
			// f->img[y * WIDTH + x] = (i << 21) + (i << 10) + i * 8;
		}
		mlx_put_image_to_window(f->mlx, f->win, f->img_ptr, 0, 0);
	}
	return (1);
}