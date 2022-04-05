/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:38:31 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 15:55:20 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_htoi(char *str)
{
	int	num;

	num = 0;
	while (*str)
	{
		num *= 16;
		if (*str >= 'a' && *str <= 'f')
			num += (*str - 'a') + 10;
		else if (*str >= 'A' && *str <= 'F')
			num += (*str - 'A') + 10;
		else
			num += *str - '0';
		str++;
	}
	return (num);
}
