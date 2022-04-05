/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:46:05 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 18:31:45 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	get_size(t_fdf *fdf, char *file)
{
	int		map_fd;
	char	*line;

	map_fd = open(file, O_RDONLY);
	if (map_fd < 0)
		print_error(fdf, strerror(errno));
	line = get_next_line(map_fd);
	fdf->map->length = 0;
	fdf->map->width = 0;
	while (line && check_line_length(fdf, line))
	{
		fdf->map->length++;
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	if (line || !fdf->map->length)
	{
		free(line);
		print_error(fdf, "Error: invalid line length found in map\n");
	}
}

static void	get_data(t_fdf *fdf, char *line, int index)
{
	int		i;
	char	**split;
	int		*heights;
	int		*highlights;

	i = 0;
	split = ft_split(line, ' ');
	heights = malloc(fdf->map->width * sizeof(int));
	highlights = malloc(fdf->map->width * sizeof(int));
	while (split[i])
	{
		heights[i] = ft_atoi(split[i]);
		if (ft_strchr(split[i], ','))
			highlights[i] = ft_htoi(ft_strchr(split[i], ',') + 3);
		else
			highlights[i] = 0;
		i++;
	}
	ft_freestrs(split);
	fdf->map->heights[index] = heights;
	fdf->map->highlights[index] = highlights;
}

static void	read_map(t_fdf *fdf, char *file)
{
	int		i;
	int		map_fd;
	char	*line;

	i = 0;
	map_fd = open(file, O_RDONLY);
	if (map_fd < 0)
		print_error(fdf, strerror(errno));
	line = get_next_line(map_fd);
	while (line)
	{
		get_data(fdf, line, i);
		free(line);
		line = get_next_line(map_fd);
		i++;
	}
	close(map_fd);
}

void	get_coords(t_fdf *fdf, int init)
{
	int	row;
	int	col;

	row = 0;
	if (init)
		fdf->map->coords = malloc(fdf->map->length * sizeof(t_coord *));
	while (row < fdf->map->length)
	{
		if (init)
			fdf->map->coords[row] = malloc(fdf->map->width * sizeof(t_coord));
		col = 0;
		fdf->map->coords[row][col].x = 0;
		fdf->map->coords[row][col].y = row * fdf->map->size;
		fdf->map->coords[row][col].z = fdf->map->heights[row][col];
		while (++col < fdf->map->width)
		{
			fdf->map->coords[row][col].x = fdf->map->coords[row][col - 1].x;
			fdf->map->coords[row][col].x += fdf->map->size;
			fdf->map->coords[row][col].y = fdf->map->coords[row][0].y;
			fdf->map->coords[row][col].z = fdf->map->heights[row][col];
		}
		row++;
	}
}

void	get_map(t_fdf *fdf, char *file)
{
	int		i;

	i = 0;
	fdf->map = malloc(sizeof(t_map));
	get_size(fdf, file);
	fdf->map->size = fdf->x_size / fdf->map->width / 2 + 1;
	fdf->map->heights = malloc(fdf->map->length * sizeof(int *));
	fdf->map->highlights = malloc(fdf->map->length * sizeof(int *));
	fdf->map->user_height = 0;
	fdf->map->user_highlight = 0xFF0000;
	fdf->map->user_translation.x = 0;
	fdf->map->user_translation.y = 0;
	fdf->map->rotation.x = 0;
	fdf->map->rotation.y = 0;
	fdf->map->rotation.z = 0;
	fdf->map->isometric = 1;
	read_map(fdf, file);
	get_coords(fdf, 1);
}
