/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:45:32 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/30 16:25:08 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** Functions to handle keyboard, mouse position and scroll
*/

int ft_funcs(int key, t_fract *fract) {
	if (key == R) {
		if (!strcmp(fract->set, "Julia"))
			ft_reset_julia(fract);
		else if (!strcmp(fract->set, "Mandelbrot"))
		    ft_reset_mandelbrot(fract);
		else if (!strcmp(fract->set, "Tricorn"))
		    ft_reset_tricorn(fract);
		else if (!strcmp(fract->set, "Burning Ship"))
		    ft_reset_burning(fract);
	}
	else if (key == W)
		fract->moveY -= (double)(0.05 / fract->zoom);
	else if (key == S)
		fract->moveY += (double)(0.05 / fract->zoom);
	else if (key == D)
		fract->moveX += (double)(0.05 / fract->zoom);
	else if (key == A)
		fract->moveX -= (double)(0.05 / fract->zoom);
	else if (key == PLUS)
		fract->iterations += 15;
	else if (key == MINUS && fract->iterations > 15)
		fract->iterations -= 15;
	else if (key == X)
		fract->locked = fract->locked == 1 ? 0 : 1;
	else if (key == ESC)
		ft_freeAll(fract);    
	return (0);    
}

int ft_scroll(int key, int x, int y, t_fract *fract) {
	(void) x;
	(void) y;
	
	/*
	** if (x >= (WIDTH / 2))
	**     fract->moveX = (double)(-1 * x / WIDTH);
	** else
	**     fract->moveX = (double)((WIDTH - x) / WIDTH);
	** if (y >= (HEIGHT / 2))
	**     fract->moveY = (double)(y / HEIGHT);
	** else
	**     fract->moveY = (double)((HEIGHT - y) / HEIGHT);
	*/

	if (key == SCROLL_UP)
		fract->zoom = fract->zoom * 1.5;
	else if (key == SCROLL_DOWN)
		fract->zoom = fract->zoom / 1.5;

	return (0);
}

int				ft_movement(int x, int y, t_fract *fract) {
	if (!ft_strcmp(fract->set, "Julia") && !fract->locked)
	{
		if (x >= WIDTH / 2)
			fract->cIm += (double)(x * 0.000005);
		else
			fract->cIm -= (double)(x * 0.000005);
		if (y >= HEIGHT / 2)
			fract->cRe -= (double)(y * 0.000005);
		else
			fract->cRe += (double)(y * 0.000005);
	}
	return (0);
}