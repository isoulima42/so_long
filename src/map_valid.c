/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:27:35 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/24 14:41:52 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_row(t_game *game, int i, int *p, int *e)
{
	int		j;
	char	c;

	if ((int)ft_strlen(game->map.grid[i]) != game->map.width)
		error_exit("Map is not rectangular");
	j = 0;
	while (j < game->map.width)
	{
		c = game->map.grid[i][j];
		if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
			error_exit("Invalid character in map");
		if (c == 'P')
			(*p)++;
		if (c == 'E')
			(*e)++;
		j++;
	}
}

void	check_chars(t_game *game)
{
	int	i;
	int	p;
	int	e;

	p = 0;
	e = 0;
	i = 0;
	while (i < game->map.height)
	{
		check_row(game, i, &p, &e);
		i++;
	}
	if (p != 1 || e != 1 || game->map.nb_collect < 1)
		error_exit("Map must have exactly 1P, 1E, and at least 1C");
}

void	check_walls(t_game *game)
{
	char	**g;
	int		i;
	int		j;

	g = game->map.grid;
	i = 0;
	while (i < game->map.width)
	{
		if (g[0][i] != '1' || g[game->map.height - 1][i] != '1')
			error_exit("Map not surrounded by walls");
		i++;
	}
	j = 0;
	while (j < game->map.height)
	{
		if (g[j][0] != '1' || g[j][game->map.width - 1] != '1')
			error_exit("Map not surrounded by walls");
		j++;
	}
}

void	check_map(t_game *game)
{
	check_walls(game);
	check_chars(game);
	check_path_valid(game);
}
