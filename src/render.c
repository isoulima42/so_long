/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:33:51 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/25 18:34:42 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx,
			game->map.width * TILE,
			game->map.height * TILE,
			"so_long");
	if (!game->win)
		return (0);
	return (1);
}

void	draw_tile(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->ptr,
		x * TILE, y * TILE);
}

void	draw_cell(t_game *game, int j, int i)
{
	int		m;
	char	c;

	c = game->map.grid[i][j];
	m = floor_mask(&game->map, j, i);
	if (c == '1')
		draw_tile(game, &game->wall, j, i);
	else if (c == 'C')
		draw_tile(game, &game->collect[m], j, i);
	else if (c == 'E')
		draw_tile(game, &game->exit_img[m], j, i);
	else if (c == 'P')
		draw_tile(game, &game->player[m], j, i);
	else
		draw_tile(game, &game->floor[m], j, i);
}

void	render_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			draw_cell(game, j, i);
			j++;
		}
		i++;
	}
}
