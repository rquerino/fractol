/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 22:30:31 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/29 16:53:11 by rquerino         ###   ########.fr       */
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
# define X				7
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
	int			thread;

	double		zoom;
	double		moveX;
	double		moveY;
	int			iterations;
	char		*set;
	int			locked;

	/* constants for shape: cRe(constant real) and cIm(constant imaginary) */
	double		cRe;
	double		cIm;

	/* Doubles needed for calculation (new/old real and imaginary) */
	double		newRe;
	double		newIm; 
	double		oldRe;
	double		oldIm;

	/* Mandelbrot pr and pi (initial real and imaginary part of z) */
	double		pr;
	double		pi;
}					t_fract;


t_fract			*ft_init_struct(char *set);
void			ft_init_env(t_fract *fract);
void			ft_freeAll(t_fract *fract);
int 			ft_funcs(int key, t_fract *fract);
int 			ft_scroll(int key, int x, int y, t_fract *fract);
int				ft_movement(int x, int y, t_fract *fract);
void			ft_reset_julia(t_fract *f);
int				ft_julia_calc(t_fract *f);
int				ft_draw_julia(t_fract *f);

void			ft_reset_mandelbrot(t_fract *f);
int				ft_mandelbrot_calc(t_fract *f);
int				ft_draw_mandelbrot(t_fract *f);

void			ft_random_color(t_fract *f);
int				ft_get_light(int start, int end, double percentage);
int				ft_get_color(t_fract *f, int i);

#endif