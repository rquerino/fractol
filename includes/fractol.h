/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 22:30:31 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/28 14:37:23 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH  		640 //1366
# define HEIGHT 		480 //768
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define W				13
# define W				13
# define A				0
# define S				1
# define D				2
# define R				15
# define PLUS			24
# define MINUS			27
# define UP				126
# define DOWN			125
# define ESC			53


typedef struct		s_color
{
	int		r;
	int		g;
	int		b;
}					t_color;

typedef struct		s_fract
{
    void    	*mlx;
	void    	*win;
	void		*img_ptr;
	uint32_t	*img;
	int			fractSet;
	t_color		*color;

	double		zoom;
	double		moveX;
	double		moveY;
	int			iterations;
	char		*set;

	//constants for shape: cRe(constant real) and cIm(constant imaginary)
    double		cRe;
    double		cIm;
	// int		width;
	// int		height;
	// int		coord_x;
	// int		coord_y;
	// int		x0;
	// int		x1;
	// int		y0;
	// int		y1;
	// int		scale;
	// int		camera;
}					t_fract;

#endif