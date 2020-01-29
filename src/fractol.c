/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:20:02 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/28 20:14:02 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"
#include <stdio.h>

/*
** gcc -Wall -Wextra -Werror -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit src/fractol.c
** Learn: complex numbers, optimization
** Allowed: open, read, write, close, malloc, free, perror, strerror, exit
*/

int ft_draw_julia(t_fract *fract)
{
    // mlx_clear_window(fract->mlx, fract->win);
    //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
    double    newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
    unsigned long   color;

    //loop through every pixel
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++)
        {
            //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
            newRe = 1.5 * (x - HEIGHT / 2) / (0.5 * fract->zoom * WIDTH) + fract->moveX;
            newIm = (y - WIDTH / 2) / (0.5 * fract->zoom * HEIGHT) + fract->moveY;
            //i will represent the number of iterations
            int i;
            //start the iteration process
            for(i = 0; i < fract->iterations; i++)
            {
                //remember value of previous iteration
                oldRe = newRe;
                oldIm = newIm;
                //the actual iteration, the real and imaginary part are calculated
                newRe = oldRe * oldRe - oldIm * oldIm + fract->cRe;
                newIm = 2 * oldRe * oldIm + fract->cIm;
                //if the point is outside the circle with radius 2: stop
                if((newRe * newRe + newIm * newIm) > 4) break;
            }

            //use color model conversion to get rainbow palette, make brightness black if fract->iterations reached
            fract->color->r = i % 255 * (i < fract->iterations);
            fract->color->g = i % 255 * (i < fract->iterations);
            fract->color->b = i % 255 * (i < fract->iterations);

            color = ((fract->color->r << 16) | (fract->color->g << 8) | fract->color->b);
            // color = ((((fract->color->R >> 16) & 0xFF) << 16) | (((fract->color->G >> 8) & 0xFF) << 8) | (fract->color->B & 0xff));

            //draw the pixel
            fract->img[y * WIDTH + x] = color;
            // fract->img[y *  + x] = (i << 21) + (i << 10) + i * 8
            // mlx_pixel_put(fract->mlx, fract->win, x, y, color);
        }
        mlx_put_image_to_window(fract->mlx, fract->win, fract->img_ptr, 0, 0);
    }
    return (1);
}

int ft_funcs(int key, t_fract *fract)
{
	if (key == R) {
        fract->zoom = 1;
        fract->moveX = -0.7;
        fract->moveY = 0.8;
        fract->iterations = 150;
    }
	else if (key == W)
		fract->moveY -= 0.005;
    else if (key == S)
		fract->moveY += 0.005;
    else if (key == D)
		fract->moveX += 0.005;
    else if (key == A)
		fract->moveX -= 0.005;
    else if (key == PLUS)
        fract->iterations += 15;
    else if (key == MINUS && fract->iterations > 15)
        fract->iterations -= 15;
	else if (key == ESC)
		exit(0);
    // if (key == UP)
    //     fract->zoom += 0.1;
    // else if (key == DOWN && fract->zoom > (1 + 0.1))
    //     fract->zoom -= 0.1;
    
    return (0);    
    // if (fract->set == "Julia")
    //     return (ft_draw_fract(fract));
    // else if (fract->set == "Mandelbrot")
    //     return (ft_draw_mandelbrot(fract));
    // else
    //     return (ft_draw_other(fract));
    // return(1);
}

int ft_scroll(int key, int x, int y, t_fract *fract)
{
    (void) x;
    (void) y;
    // Try to fix the zoom following the mouse
    // if (x >= (WIDTH / 2))
    //     fract->moveX += (x / WIDTH);
    // else
    //     fract->moveX -= ((WIDTH - x) / WIDTH);
    // if (y >= (HEIGHT / 2))
    //     fract->moveY += (y / HEIGHT);
    // else
    //     fract->moveY -= ((HEIGHT - y) / HEIGHT);

    if (key == SCROLL_UP)
        fract->zoom = fract->zoom * 1.5;
	else if (key == SCROLL_DOWN)
        fract->zoom = fract->zoom / 1.5;

	return (0);
}


int				ft_movement(int x, int y, t_fract *fract)
{
	if (ft_strcmp(fract->set, "Julia") == 0)
	{
		fract->cIm += (double)(x * 0.00001);
		fract->cRe -= (double)(y * 0.00001);
	}
	return (0);
}

void    freeAll(t_fract *fract) {
	mlx_clear_window(fract->mlx, fract->win);
	mlx_destroy_window(fract->mlx, fract->win);
	exit(0);
    free(fract);
}

/*
Quadratic Julia Sets
    1) For every pixel: Znew = Zold^2 + C, radius = 2. The number of iterations is the color of the pixel
    2) The screen represents a part of the complex plano, inside the circle with radius 2 around the origin.
        For a pixel, x coord represents the real part of its complex coordinates, and y coord will be the imaginary part.
    3) The value of the initial pixel you apply the function, Z can go to infinity or remain in the circle with radius 2.
        Those that remain are the ones that belong to the Julia set.


 */

int main(int ac, char **av) {
    if (ac == 1) {
        int		bpp;
        int		size;
        int		endian;


    // if (ac == 2 && (av[1] == "Julia" || av[1] == "Mandelbrot")) {
        t_fract   *fract;
        fract = malloc(sizeof(t_fract));
        fract->color = malloc(sizeof(t_color));
        // function to initialize variables
        fract->set = av[1];
        // Mouse scroll up/down
        fract->zoom = 1.0;
        // keyboard keys WASD
        fract->moveX = -0.7;
        fract->moveY = 0.8;
        // +/- keyboard
        fract->iterations = 150;
        // Change by mouse moving
        fract->cRe = -0.7;
        fract->cIm = 0.27015;

        fract->mlx = mlx_init();
        fract->win = mlx_new_window(fract->mlx, WIDTH, HEIGHT, "Fract'ol");
        // init, mlx_new_window, mlx_new_image and mlx_get_data_addr can be in another function with the int variables
        fract->img_ptr = mlx_new_image(fract->mlx, WIDTH, HEIGHT);
        fract->img = (uint32_t*)mlx_get_data_addr(fract->img_ptr, &bpp, &size, &endian);

        // Key press
        mlx_hook(fract->win, 2, 0, ft_funcs, fract);
        // Mouse press
        mlx_hook(fract->win, 4, 0, ft_scroll, fract);
        // Mouse move
        // mlx_hook(fract->win, 6, 0, ft_movement, fract);
        mlx_loop_hook(fract->mlx, ft_draw_julia, fract);
        mlx_loop(fract->mlx);
        freeAll(fract);
    } else {
        // ft_putstr("Usage: ./ft_fractal set\n");
        // ft_putstr("Sets available: Julia, Mandelbrot, x.\n");
    }
    
    return (0);
}