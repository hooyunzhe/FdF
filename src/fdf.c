/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:33:35 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 18:31:25 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	close_window(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img->img);
	mlx_destroy_window(fdf->mlx, fdf->window);
	ft_freeints(fdf->map->heights, fdf->map->length);
	ft_freeints(fdf->map->highlights, fdf->map->length);
	while (fdf->map->length--)
		free(fdf->map->coords[fdf->map->length]);
	free(fdf->map->coords);
	free(fdf->map);
	free(fdf->img);
	free(fdf);
	exit(0);
}

void	keyhook_handler_2(int keycode, t_fdf *fdf)
{
	if (keycode == 12 && fdf->map->size > (fdf->x_size / fdf->map->width / 3))
		fdf->map->size -= fdf->x_size / fdf->map->width / 3;
	if (keycode == 14)
		fdf->map->size += fdf->x_size / fdf->map->width / 3;
	if (keycode == 3)
		fdf->map->user_height -= 1;
	if (keycode == 5)
		fdf->map->user_height += 1;
	if (keycode == 48)
		fdf->map->isometric *= -1;
	if (keycode == 18)
		fdf->map->user_highlight = 0xFFFFFF;
	if (keycode == 19)
		fdf->map->user_highlight = 0xFF0000;
	if (keycode == 20)
		fdf->map->user_highlight = 0x00FF00;
	if (keycode == 21)
		fdf->map->user_highlight = 0x0000FF;
	if (keycode == 4)
		fdf->hud_state *= -1;
}

int	keyhook_handler(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		close_window(fdf);
	if (keycode == 0 || keycode == 123)
		fdf->map->user_translation.x += 3;
	if (keycode == 2 || keycode == 124)
		fdf->map->user_translation.x -= 3;
	if (keycode == 13 || keycode == 126)
		fdf->map->user_translation.y += 3;
	if (keycode == 1 || keycode == 125)
		fdf->map->user_translation.y -= 3;
	if (keycode == 6)
		fdf->map->rotation.x -= 10;
	if (keycode == 7)
		fdf->map->rotation.x += 10;
	if (keycode == 8)
		fdf->map->rotation.y -= 10;
	if (keycode == 9)
		fdf->map->rotation.y += 10;
	if (keycode == 11)
		fdf->map->rotation.z -= 10;
	if (keycode == 45)
		fdf->map->rotation.z += 10;
	keyhook_handler_2(keycode, fdf);
	return (0);
}

int	render_frame(t_fdf *fdf)
{
	get_coords(fdf, 0);
	transform_map(fdf);
	rotate_map_3d(fdf, deg_to_rad(fdf->map->rotation.x),
		deg_to_rad(fdf->map->rotation.y), deg_to_rad(fdf->map->rotation.z));
	translate_map(fdf);
	mlx_destroy_image(fdf->mlx, fdf->img->img);
	get_image(fdf, 0);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img->img, 0, 0);
	if (fdf->hud_state == 1)
		draw_keybinds(fdf);
	else
		draw_hud(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		print_error(NULL, "Error: please provide a valid path to the map...\n");
	fdf = malloc(sizeof(t_fdf));
	fdf->x_size = 1920;
	fdf->y_size = 1080;
	get_map(fdf, argv[1]);
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, fdf->x_size, fdf->y_size, "fdf");
	fdf->hud_state = 1;
	get_image(fdf, 1);
	transform_map(fdf);
	translate_map(fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img->img, 0, 0);
	mlx_key_hook(fdf->window, keyhook_handler, fdf);
	mlx_hook(fdf->window, 17, 0, close_window, fdf);
	mlx_loop_hook(fdf->mlx, render_frame, fdf);
	mlx_loop(fdf->mlx);
}
