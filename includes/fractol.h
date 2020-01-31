/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 22:30:31 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/31 12:51:45 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH  		640
# define HEIGHT 		480
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define R				15
# define X				7
# define C				8
# define PLUS			24
# define MINUS			27
# define LEFT			123
# define RIGHT			124
# define DOWN			125
# define UP				126
# define ESC			53

typedef struct			s_fract
{
	void				*mlx;
	void				*win;
	void				*img_ptr;
	uint32_t			*img;
	int					color_base;
	int					monochromatic;
	double				zoom;
	double				move_x;
	double				move_y;
	int					iterations;
	char				*set;
	int					locked;
	double				c_re;
	double				c_im;
	double				n_re;
	double				n_im;
	double				o_re;
	double				o_im;
	double				pr;
	double				pi;
	double				x;
	double				y;
}						t_fract;

t_fract					*ft_init_struct(char *set);
void					ft_init_env(t_fract *fract);
void					ft_free_all(t_fract *fract);
void					ft_reset(t_fract *f);
int						ft_funcs(int key, t_fract *fract);
int						ft_scroll(int key, int x, int y, t_fract *fract);
int						ft_movement(int x, int y, t_fract *fract);
void					ft_reset_julia(t_fract *f);
int						ft_julia_calc(t_fract *f);
int						ft_draw_julia(t_fract *f);
void					ft_reset_mandelbrot(t_fract *f);
int						ft_mandelbrot_calc(t_fract *f);
int						ft_draw_mandelbrot(t_fract *f);
void					ft_reset_tricorn(t_fract *f);
int						ft_tricorn_calc(t_fract *f);
int						ft_draw_tricorn(t_fract *f);
void					ft_reset_burning(t_fract *f);
int						ft_burning_calc(t_fract *f);
int						ft_draw_burning(t_fract *f);
int						ft_getcolor(t_fract *f, int i);

#endif
