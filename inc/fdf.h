#ifndef FDF_H
# define FDF_H

#include "../mlx/mlx.h"
#include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}		t_coord;

typedef struct s_map
{
	int		length;
	int		width;
	int		**heights;
	int		user_height;
	int		size;
	t_coord	rotation;
	t_coord	line[2];
	t_coord	center;
	t_coord	center_translation;
	t_coord	user_translation;
	t_coord	**coords;
	int		**highlights;
	int		user_highlight;
	int		color;
	int		isometric;
}		t_map;

typedef	struct s_img
{
	void	*img;
	char	*addr;
	int		bbp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_fdf
{
	t_map	*map;
	t_img	*img;
	void	*mlx;
	void	*window;
	int		x_size;
	int		y_size;
	int		hud_state;
}			t_fdf;

double	deg_to_rad(double deg);
void	print_error(t_fdf *fdf, char *error);
int		check_out_of_bounds(t_fdf *fdf, t_coord coord);
int		check_line_length(t_fdf *fdf, char *line);
char	*get_next_line(int fd);
void	get_coords(t_fdf *fdf, int init);
void	get_image(t_fdf *fdf, int init);
void	get_map(t_fdf *fdf, char *file);
void	get_color(t_fdf *fdf, int row, int col, int vertical);
void	transform_map(t_fdf *fdf);
void	translate_map(t_fdf *fdf);
void	rotate_map(t_fdf *fdf, double h_rad, double v_rad);
void	rotate_map_3d(t_fdf *fdf, double x_rad, double y_rad, double z_rad);
void	draw_map(t_fdf *fdf);
void	draw_keybinds(t_fdf *fdf);
void	draw_hud(t_fdf *fdf);

#endif