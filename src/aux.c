/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:45:32 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/30 20:32:48 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_reset(t_fract *f)
{
	if (!strcmp(f->set, "Julia"))
		ft_reset_julia(f);
	else if (!strcmp(f->set, "Mandelbrot"))
		ft_reset_mandelbrot(f);
	else if (!strcmp(f->set, "Tricorn"))
		ft_reset_tricorn(f);
	else if (!strcmp(f->set, "Burning Ship"))
		ft_reset_burning(f);
}

/*
** Functions to handle keyboard, mouse position and scroll
*/

int		ft_funcs(int key, t_fract *fract)
{
	if (key == R)
		ft_reset(fract);
	else if (key == W)
		fract->move_y -= (double)(0.05 / fract->zoom);
	else if (key == S)
		fract->move_y += (double)(0.05 / fract->zoom);
	else if (key == D)
		fract->move_x += (double)(0.05 / fract->zoom);
	else if (key == A)
		fract->move_x -= (double)(0.05 / fract->zoom);
	else if (key == PLUS)
		fract->iterations += 15;
	else if (key == MINUS && fract->iterations > 15)
		fract->iterations -= 15;
	else if (key == X)
		fract->locked = fract->locked == 1 ? 0 : 1;
	else if (key == C)
		fract->monochromatic = fract->monochromatic == 1 ? 0 : 1;
	else if (key == ESC)
		ft_free_all(fract);
	return (0);
}

/*
** Add zoom to follow mouse
*/

int		ft_scroll(int key, int x, int y, t_fract *fract)
{
	(void)x;
	(void)y;
	if (key == SCROLL_UP)
		fract->zoom = fract->zoom * 1.5;
	else if (key == SCROLL_DOWN)
		fract->zoom = fract->zoom / 1.5;
	return (0);
}

int		ft_movement(int x, int y, t_fract *fract)
{
	if (!ft_strcmp(fract->set, "Julia") && !fract->locked)
	{
		if (x >= WIDTH / 2)
			fract->c_im += (double)(x * 0.000005);
		else
			fract->c_im -= (double)(x * 0.000005);
		if (y >= HEIGHT / 2)
			fract->c_re -= (double)(y * 0.000005);
		else
			fract->c_re += (double)(y * 0.000005);
	}
	return (0);
}
