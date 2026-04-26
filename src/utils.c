/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:17:44 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/25 18:28:14 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_wall(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	return (map->grid[y][x] == '1');
}

int	floor_mask(t_map *map, int x, int y)
{
	int	m;

	m = 0;
	if (is_wall(map, x, y - 1))
		m |= 1;
	if (is_wall(map, x + 1, y))
		m |= 2;
	if (is_wall(map, x, y + 1))
		m |= 4;
	if (is_wall(map, x - 1, y))
		m |= 8;
	return (m);
}

void	parse_row(t_game *game, int i)
{
	int		j;
	char	c;

	j = 0;
	while (j < game->map.width)
	{
		c = game->map.grid[i][j];
		if (c == 'C')
			game->map.nb_collect++;
		if (c == 'P')
		{
			game->map.p_x = j;
			game->map.p_y = i;
		}
		j++;
	}
}

void	parse_map(t_game *game)
{
	int	h;
	int	i;

	h = 0;
	while (game->map.grid[h])
		h++;
	game->map.height = h;
	game->map.width = (int)ft_strlen(game->map.grid[0]);
	game->map.nb_collect = 0;
	i = 0;
	while (i < h)
	{
		parse_row(game, i);
		i++;
	}
}
