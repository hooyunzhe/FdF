/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:55:23 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 15:07:24 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	put_coord(t_fdf *fdf, int x, int y, t_coord value)
{
	int		i;
	char	*coord_x;
	char	*coord_y;
	char	*str;

	i = 0;
	coord_x = ft_itoa(value.x);
	coord_y = ft_itoa(value.y);
	str = malloc((ft_strlen(coord_x) + ft_strlen(coord_y) + 5) * sizeof(char));
	str[i++] = '(';
	while (*coord_x)
		str[i++] = *coord_x++;
	str[i++] = ',';
	str[i++] = ' ';
	while (*coord_y)
		str[i++] = *coord_y++;
	str[i++] = ')';
	str[i] = 0;
	mlx_string_put(fdf->mlx, fdf->window, x, y, 0xFFFFFF, str);
	free(str);
}

static void	put_rotation(t_fdf *fdf, int x, int y, int deg)
{
	int		i;
	char	*deg_str;
	char	*str;

	i = 0;
	deg_str = ft_itoa(deg);
	str = malloc((ft_strlen(deg_str) + 5) * sizeof(char));
	while (*deg_str)
		str[i++] = *deg_str++;
	str[i++] = ' ';
	str[i++] = 'd';
	str[i++] = 'e';
	str[i++] = 'g';
	str[i] = 0;
	mlx_string_put(fdf->mlx, fdf->window, x, y, 0xFFFFFF, str);
	free(str);
}

static void	put_px(t_fdf *fdf, t_coord coord, int px, int p)
{
	int		i;
	char	*px_str;
	char	*str;

	i = 0;
	px_str = ft_itoa(px);
	str = malloc((ft_strlen(px_str) + 2 + p) * sizeof(char));
	while (*px_str)
		str[i++] = *px_str++;
	if (p)
		str[i++] = 'p';
	str[i++] = 'x';
	str[i] = 0;
	mlx_string_put(fdf->mlx, fdf->window, coord.x, coord.y, 0xFFFFFF, str);
	free(str);
}

void	draw_hud(t_fdf *fdf)
{
	t_coord	coord;

	mlx_string_put(fdf->mlx, fdf->window, 50, 50, 0x808080, "Top Left:");
	put_coord(fdf, 50, 75, fdf->map->coords[0][0]);
	mlx_string_put(fdf->mlx, fdf->window, 50, 125, 0x808080, "Rotation:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 150, 0x808080, "X: ");
	put_rotation(fdf, 80, 150, fdf->map->rotation.x);
	mlx_string_put(fdf->mlx, fdf->window, 50, 175, 0x808080, "Y: ");
	put_rotation(fdf, 80, 175, fdf->map->rotation.y);
	mlx_string_put(fdf->mlx, fdf->window, 50, 200, 0x808080, "Z: ");
	put_rotation(fdf, 80, 200, fdf->map->rotation.z);
	mlx_string_put(fdf->mlx, fdf->window, 50, 250, 0x808080, "Size:");
	coord.x = 50;
	coord.y = 275;
	put_px(fdf, coord, fdf->map->size, 1);
	mlx_string_put(fdf->mlx, fdf->window, 50, 325, 0x808080, "Height:");
	coord.x = 50;
	coord.y = 350;
	put_px(fdf, coord, fdf->map->user_height, 0);
}

void	draw_keybinds(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->window, 50, 50, 0x808080, "Camera Movement:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 75, 0xFFFFFF, "WASD/Arrow Keys");
	mlx_string_put(fdf->mlx, fdf->window, 50, 125, 0x808080, "Zoom:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 150, 0xFFFFFF, "Q/E");
	mlx_string_put(fdf->mlx, fdf->window, 50, 200, 0x808080, "Rotate:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 225, 0x808080, "X:  Y:  Z:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 250, 0xFFFFFF, "Z/X C/V B/N");
	mlx_string_put(fdf->mlx, fdf->window, 50, 300, 0x808080, "Height:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 325, 0xFFFFFF, "F/G");
	mlx_string_put(fdf->mlx, fdf->window, 50, 375, 0x808080, "Perspective:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 400, 0x808080, "Isometric");
	mlx_string_put(fdf->mlx, fdf->window, 140, 400, 0x808080, "/Parallel:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 425, 0xFFFFFF, "Tab");
	mlx_string_put(fdf->mlx, fdf->window, 50, 475, 0x808080, "Colors:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 500, 0xFFFFFF, "White: 1");
	mlx_string_put(fdf->mlx, fdf->window, 50, 525, 0xFF0000, "Red: 2");
	mlx_string_put(fdf->mlx, fdf->window, 50, 550, 0x00FF00, "Green: 3");
	mlx_string_put(fdf->mlx, fdf->window, 50, 575, 0x0000FF, "Blue: 4");
	mlx_string_put(fdf->mlx, fdf->window, 50, 625, 0x808080, "HUD:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 650, 0xFFFFFF, "H");
	mlx_string_put(fdf->mlx, fdf->window, 50, 700, 0x808080, "Exit:");
	mlx_string_put(fdf->mlx, fdf->window, 50, 725, 0xFFFFFF, "Escape");
}
