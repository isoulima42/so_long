/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:48:09 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/24 14:47:33 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_grid(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		error_exit("Memory error");
	i = 0;
	while (i < game->map.height)
	{
		copy[i] = ft_strdup(game->map.grid[i]);
		if (!copy[i])
			error_exit("Memory error");
		i++;
	}
	copy[game->map.height] = NULL;
	return (copy);
}

void	flood_fill(char **grid, int x, int y)
{
	if (x < 0 || y < 0 || !grid[y] || !grid[y][x])
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	flood_fill(grid, x + 1, y);
	flood_fill(grid, x - 1, y);
	flood_fill(grid, x, y + 1);
	flood_fill(grid, x, y - 1);
}

void	check_path_valid(t_game *game)
{
	char	**copy;
	int		i;
	int		j;

	copy = copy_grid(game);
	flood_fill(copy, game->map.p_x, game->map.p_y);
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (copy[i][j] == 'C' || copy[i][j] == 'E')
				error_exit("No valid path to all collectibles and exit");
			j++;
		}
		i++;
	}
	free_map(copy);
}
