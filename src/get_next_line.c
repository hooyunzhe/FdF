/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:56:52 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 15:00:27 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static char	*get_current_line(int rv, char **str)
{
	char	*newline;
	char	*temp;
	char	*line;

	newline = ft_strchr(*str, '\n');
	temp = NULL;
	line = NULL;
	if (newline)
	{
		line = ft_strtrimchr(*str, '\n');
		if (*(newline + 1))
			temp = ft_strdup(newline + 1);
	}
	else if (rv == 0 && *str && **str)
		line = ft_strdup(*str);
	if (*str)
		free(*str);
	*str = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	int			rv;

	if (fd < 0)
		return (NULL);
	buffer = malloc((1000 * sizeof(char)) + 1);
	if (!buffer)
		return (NULL);
	rv = 1;
	while (rv > 0 && !ft_strchr(str, '\n'))
	{
		rv = read(fd, buffer, 1000);
		buffer[rv] = 0;
		if (rv >= 0)
			str = ft_strupdate(str, buffer);
		if (!str)
			rv = -1;
	}
	free(buffer);
	buffer = NULL;
	return (get_current_line(rv, &str));
}
