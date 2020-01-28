/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquerino <rquerino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:20:02 by rquerino          #+#    #+#             */
/*   Updated: 2020/01/27 18:17:45 by rquerino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"

/*
** gcc -Wall -Wextra -Werror -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit src/fractol.c
** Learn: complex numbers, optimization
** Allowed: open, read, write, close, malloc, free, perror, strerror, exit
*/

int    ft_draw_julia(t_fract *fract)
{
    mlx_clear_window(fract->mlx, fract->win);
    //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
    double    cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
    double    newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
    unsigned long   color;

    //pick some values for the constant c, this determines the shape of the Julia Set
    cRe = -0.7;
    cIm = 0.27015;

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
                newRe = oldRe * oldRe - oldIm * oldIm + cRe;
                newIm = 2 * oldRe * oldIm + cIm;
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
            mlx_pixel_put(fract->mlx, fract->win, x, y, color);
        }
    }
    return (1);
}

int		ft_funcs(int key, t_fract *fract)
{
	if (key == R) {
        fract->zoom = 1;
        fract->moveX = 0;
        fract->moveY = 0;
        fract->iterations = 300;
    }
    else if (key == UP)
		fract->zoom += 0.1;
	else if ((key == DOWN) && (fract->zoom > 0.1))
		fract->zoom -= 0.1;
	else if (key == W)
		fract->moveY += 0.1;
    else if (key == S)
		fract->moveY -= 0.1;
    else if (key == D)
		fract->moveX += 0.1;
    else if (key == A)
		fract->moveX -= 0.1;
    else if (key == PLUS)
        fract->iterations += 25;
    else if (key == MINUS && fract->iterations > 25)
        fract->iterations -= 25;
	else if (key == ESC)
		exit(0);
    return (ft_draw_julia(fract));    
    // if (fract->set == "Julia")
    //     return (ft_draw_fract(fract));
    // else if (fract->set == "Mandelbrot")
    //     return (ft_draw_mandelbrot(fract));
    // else
    //     return (ft_draw_other(fract));
    // return(1);
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
    if (ac == 2) {
    // if (ac == 2 && (av[1] == "Julia" || av[1] == "Mandelbrot")) {
        t_fract   *fract;
        fract = malloc(sizeof(t_fract));
        fract->color = malloc(sizeof(t_color));
        // function to initialize variables
        fract->set = av[1];
        fract->zoom = 1;
        fract->moveX = -0.7;
        fract->moveY = 0.8;
        fract->iterations = 100;

        fract->mlx = mlx_init();
        fract->win = mlx_new_window(fract->mlx, WIDTH, HEIGHT, "Fract'ol");
        ft_draw_julia(fract);
        mlx_hook(fract->win, 2, 0, ft_funcs, fract);
        // mlx_loop_hook(fract->mlx, ft_draw, fract);
        // ft_draw(fract);
        mlx_loop(fract->mlx);
        free(fract);
    } else {
        // ft_putstr("Usage: ./ft_fractal set\n");
        // ft_putstr("Sets available: Julia, Mandelbrot, x.\n");
    }
    
    return (0);
}