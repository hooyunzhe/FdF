/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:56:19 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 18:30:40 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}

int	check_out_of_bounds(t_fdf *fdf, t_coord coord)
{
	if (coord.x <= 0 || coord.x >= fdf->x_size
		|| coord.y <= 0 || coord.y >= fdf->y_size)
		return (1);
	return (0);
}

void	get_image(t_fdf *fdf, int init)
{
	if (init)
		fdf->img = malloc(sizeof(t_img));
	fdf->img->img = mlx_new_image(fdf->mlx, fdf->x_size, fdf->y_size);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img, &fdf->img->bbp,
			&fdf->img->line_len, &fdf->img->endian);
}

void	print_error(t_fdf *fdf, char *error)
{
	if (fdf)
	{
		free(fdf->map);
		free(fdf);
	}
	write(1, error, ft_strlen(error));
	exit(-1);
}

int	check_line_length(t_fdf *fdf, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!fdf->map->width)
		fdf->map->width = ft_strslen(split);
	if ((int)ft_strslen(split) != fdf->map->width)
	{
		ft_freestrs(split);
		return (0);
	}
	ft_freestrs(split);
	return (1);
}
