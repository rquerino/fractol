/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:20:02 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/30 16:31:58 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

/*
** Learn: complex numbers, optimization
** Allowed: open, read, write, close, malloc, free, perror, strerror, exit
*/

/*
** Initialize struct
*/

t_fract		*ft_init_struct(char *set) {
	if (!ft_strcmp(set, "Julia") || !ft_strcmp(set, "Mandelbrot") || !ft_strcmp(set, "Tricorn") || !ft_strcmp(set, "Burning Ship")) {
		t_fract *fract;
		fract = malloc(sizeof(t_fract));
		fract->color = malloc(sizeof(t_color));
		fract->set = set;
		if (!ft_strcmp(set, "Julia"))
			ft_reset_julia(fract);
		else if (!ft_strcmp(set, "Mandelbrot"))
		    ft_reset_mandelbrot(fract);
		else if (!ft_strcmp(set, "Tricorn"))
		    ft_reset_tricorn(fract);
		else if (!ft_strcmp(set, "Burning Ship"))
		    ft_reset_burning(fract);
		return (fract);
	}
	return (NULL);
}

/*
** Initialize environment
*/

void	ft_init_env(t_fract *fract) {
	int		bpp;
	int		size;
	int		endian;

	fract->mlx = mlx_init();
	fract->win = mlx_new_window(fract->mlx, WIDTH, HEIGHT, "Fract'ol");
	fract->img_ptr = mlx_new_image(fract->mlx, WIDTH, HEIGHT);
	fract->img = (uint32_t*)mlx_get_data_addr(fract->img_ptr, &bpp, &size, &endian);
	mlx_hook(fract->win, 2, 0, ft_funcs, fract);
	mlx_hook(fract->win, 4, 0, ft_scroll, fract);
	mlx_hook(fract->win, 6, 0, ft_movement, fract);
	if (!ft_strcmp(fract->set, "Julia"))
		mlx_loop_hook(fract->mlx, ft_draw_julia, fract);
	else if (!ft_strcmp(fract->set, "Mandelbrot"))
		mlx_loop_hook(fract->mlx, ft_draw_mandelbrot, fract);
	else if (!ft_strcmp(fract->set, "Tricorn"))
		mlx_loop_hook(fract->mlx, ft_draw_tricorn, fract);
	else if (!ft_strcmp(fract->set, "Burning Ship"))
		mlx_loop_hook(fract->mlx, ft_draw_burning, fract);
	mlx_loop(fract->mlx);
}

/*
** Free memory, called when ESC is pressed.
*/

void	ft_freeAll(t_fract *fract) {
	mlx_clear_window(fract->mlx, fract->win);
	mlx_destroy_window(fract->mlx, fract->win);
	exit(0);
	free(fract);
}

/*
** Main function
*/

int		main(int ac, char **av) {
	if (ac == 2) {
		t_fract	*fract;
		fract = ft_init_struct(av[1]);
		if (fract)
			ft_init_env(fract);
		else
			ft_putstr("Please enter a valid fractal set. Available: Julia, Mandelbrot, Tricorn, Y\n");
	}
	else
		ft_putstr("Usage: ./ft_fractal <Julia, Mandelbrot, Tricorn>\n");
	return (0);
}
