/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:25:16 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 15:06:12 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	draw_pixel(t_fdf *fdf, t_coord coord)
{
	int		dist;
	char	*dest;

	if (!check_out_of_bounds(fdf, coord))
	{
		dist = (coord.x * (fdf->img->bbp / 8) + coord.y * fdf->img->line_len);
		dest = fdf->img->addr + dist;
		*(unsigned int *)dest = fdf->map->color;
	}
}

static void	draw_line_low(t_fdf *fdf, int dx, int dy)
{
	int		d;
	int		dir;
	t_coord	coord;

	dir = 1 - (2 * (dy < 0));
	if (dy < 0)
		dy *= -1;
	d = (2 * dy) - dx;
	coord = fdf->map->line[0];
	while (coord.x < fdf->map->line[1].x)
	{
		draw_pixel(fdf, coord);
		if (d > 0)
		{
			coord.y += dir;
			d -= 2 * dx;
		}
		d += 2 * dy;
		coord.x++;
	}
}

static void	draw_line_high(t_fdf *fdf, int dx, int dy)
{
	int		d;
	int		dir;
	t_coord	coord;

	dir = 1 - (2 * (dx < 0));
	if (dx < 0)
		dx *= -1;
	d = (2 * dx) - dy;
	coord = fdf->map->line[0];
	while (coord.y < fdf->map->line[1].y)
	{
		draw_pixel(fdf, coord);
		if (d > 0)
		{
			coord.x += dir;
			d -= 2 * dy;
		}
		d += 2 * dx;
		coord.y++;
	}
}

static void	draw_line(t_fdf *fdf)
{
	int	dx;
	int	dy;
	int	temp;

	dx = fdf->map->line[1].x - fdf->map->line[0].x;
	dy = fdf->map->line[1].y - fdf->map->line[0].y;
	if ((fdf->map->line[0].x > fdf->map->line[1].x && abs(dx) > abs(dy))
		|| (fdf->map->line[0].y > fdf->map->line[1].y && abs(dx) <= abs(dy)))
	{
		temp = fdf->map->line[0].x;
		fdf->map->line[0].x = fdf->map->line[1].x;
		fdf->map->line[1].x = temp;
		temp = fdf->map->line[0].y;
		fdf->map->line[0].y = fdf->map->line[1].y;
		fdf->map->line[1].y = temp;
	}
	dx = fdf->map->line[1].x - fdf->map->line[0].x;
	dy = fdf->map->line[1].y - fdf->map->line[0].y;
	if (abs(dx) > abs(dy))
		draw_line_low(fdf, dx, dy);
	else
		draw_line_high(fdf, dx, dy);
}

void	draw_map(t_fdf *fdf)
{
	int		row;
	int		col;
	t_coord	line;

	row = 0;
	while (row < fdf->map->length)
	{
		col = 0;
		while (col < fdf->map->width)
		{
			fdf->map->line[0] = fdf->map->coords[row][col];
			line = fdf->map->coords[row][col + (col < fdf->map->width - 1)];
			fdf->map->line[1] = line;
			get_color(fdf, row, col, 0);
			draw_line(fdf);
			fdf->map->line[0] = fdf->map->coords[row][col];
			line = fdf->map->coords[row + (row < fdf->map->length - 1)][col];
			fdf->map->line[1] = line;
			get_color(fdf, row, col, 1);
			draw_line(fdf);
			col++;
		}
		row++;
	}
}
