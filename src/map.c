/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:49:00 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 15:05:11 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	translate_map(t_fdf *fdf)
{
	int		row;
	int		col;
	t_coord	translation;

	row = 0;
	while (row < fdf->map->length)
	{
		col = 0;
		while (col < fdf->map->width)
		{
			fdf->map->coords[row][col].x += fdf->map->center_translation.x;
			fdf->map->coords[row][col].y += fdf->map->center_translation.y;
			translation.x = fdf->map->user_translation.x * fdf->map->size / 2;
			translation.y = fdf->map->user_translation.y * fdf->map->size / 2;
			fdf->map->coords[row][col].x += translation.x;
			fdf->map->coords[row][col].y += translation.y;
			col++;
		}
		row++;
	}
}

void	rotate_map(t_fdf *fdf, double h_rad, double v_rad)
{
	int		row;
	int		col;
	int		x;
	int		y;
	int		height;

	row = 0;
	while (row < fdf->map->length)
	{
		col = 0;
		while (col < fdf->map->width)
		{
			x = fdf->map->coords[row][col].x;
			y = fdf->map->coords[row][col].y;
			fdf->map->coords[row][col].x = x * cos(h_rad) - y * sin(v_rad);
			fdf->map->coords[row][col].y = y * cos(v_rad) + x * sin(h_rad);
			if (fdf->map->coords[row][col].z != 0)
				fdf->map->coords[row][col].z += fdf->map->user_height;
			height = fdf->map->coords[row][col].z * (fdf->map->size / 1.5);
			fdf->map->coords[row][col].y -= height;
			col++;
		}
		row++;
	}
}

void	rotate_map_3d(t_fdf *fdf, double x_rad, double y_rad, double z_rad)
{
	int	row;
	int	col;
	int	x;
	int	y;

	row = 0;
	while (row < fdf->map->length)
	{
		col = 0;
		while (col < fdf->map->width)
		{
			x = fdf->map->coords[row][col].x - fdf->map->center.x;
			y = fdf->map->coords[row][col].y - fdf->map->center.y;
			fdf->map->coords[row][col].x = x * cos(y_rad) * cos(z_rad);
			fdf->map->coords[row][col].x += y * (sin(x_rad) * sin(y_rad)
					* cos(z_rad) - cos(x_rad) * sin(z_rad));
			fdf->map->coords[row][col].y = y * (sin(x_rad) * sin(y_rad)
					* sin(z_rad) + cos(x_rad) * cos(z_rad));
			fdf->map->coords[row][col].y += x * cos(y_rad) * sin(z_rad);
			fdf->map->coords[row][col].x += fdf->map->center.x;
			fdf->map->coords[row][col].y += fdf->map->center.y;
			col++;
		}
		row++;
	}
}

void	transform_map(t_fdf *fdf)
{
	int		left_edge;
	int		right_edge;
	int		top_edge;
	int		bottom_edge;

	if (fdf->map->isometric == 1)
		rotate_map(fdf, deg_to_rad(30), deg_to_rad(60));
	left_edge = fdf->map->coords[fdf->map->length - 1][0].x;
	right_edge = fdf->map->coords[0][fdf->map->width - 1].x;
	top_edge = fdf->map->coords[0][0].y;
	bottom_edge = fdf->map->coords[fdf->map->length - 1][fdf->map->width - 1].y;
	fdf->map->center.x = (right_edge - left_edge) / 2 + left_edge;
	fdf->map->center.y = (bottom_edge - top_edge) / 2;
	fdf->map->center_translation.x = (fdf->x_size - (right_edge - left_edge));
	fdf->map->center_translation.x /= 2;
	fdf->map->center_translation.x -= left_edge;
	fdf->map->center_translation.y = (fdf->y_size - (bottom_edge - top_edge));
	fdf->map->center_translation.y /= 2;
}

void	get_color(t_fdf *fdf, int row, int col, int vertical)
{
	if (fdf->map->highlights[row][col])
		fdf->map->color = fdf->map->highlights[row][col];
	else if (fdf->map->heights[row][col])
		fdf->map->color = fdf->map->user_highlight;
	else if (vertical)
	{
		if (fdf->map->heights[row + (row < fdf->map->length - 1)][col])
			fdf->map->color = fdf->map->user_highlight;
		else
			fdf->map->color = 0xFFFFFF;
	}
	else if (fdf->map->heights[row][col + (col < fdf->map->width - 1)])
		fdf->map->color = fdf->map->user_highlight;
	else
		fdf->map->color = 0xFFFFFF;
}
