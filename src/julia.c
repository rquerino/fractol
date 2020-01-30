/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:51:48 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/29 16:41:45 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fractol.h"

void    ft_reset_julia(t_fract *f) {
	// mouse scroll
	f->zoom = 1.0;
	// keyboard keys WASD
	f->moveX = 0;
	f->moveY = 0;
	// +/- keyboard
	f->iterations = 150;
	// Change by mouse moving
	f->cRe = -0.7;
	f->cIm = 0.3;
	f->locked = 0;
}

/*
** Quadratic Julia Sets
** 1) For every pixel: Znew = Zold^2 + C, radius = 2. The number of iterations is the color of the pixel
** 2) The screen represents a part of the complex plano, inside the circle with radius 2 around the origin.
** For a pixel, x coord represents the real part of its complex coordinates, and y coord will be the imaginary part.
** 3) The value of the initial pixel you apply the function, Z can go to infinity or remain in the circle with radius 2.
** Those that remain are the ones that belong to the Julia set.
** Good link: https://lodev.org/cgtutor/juliamandelbrot.html
*/

int	ft_julia_calc(t_fract *f) {
	int	i;

	i = 0;
	while (i < f->iterations) {
		//remember value of previous iteration
		f->oldRe = f->newRe;
		f->oldIm = f->newIm;
		//the actual iteration, the real and imaginary part are calculated
		f->newRe = f->oldRe * f->oldRe - f->oldIm * f->oldIm + f->cRe;
		f->newIm = 2 * f->oldRe * f->oldIm + f->cIm;
		//if the point is outside the circle with radius 2: stop
		if((f->newRe * f->newRe + f->newIm * f->newIm) > 4) break;
		i++;
	}
	return (i);
}

int	ft_draw_julia(t_fract *f) {
	unsigned long   color;
	int				x;
	int				y;
	int				i;

	y = -1;
	while (++y < HEIGHT) {
		x = -1;
		while (++x < WIDTH) {
			//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
			f->newRe = 1.5 * (x - WIDTH / 2) / (0.5 * f->zoom * WIDTH) + f->moveX;
			f->newIm = (y - HEIGHT / 2) / (0.5 * f->zoom * HEIGHT) + f->moveY;
			i = ft_julia_calc(f);
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