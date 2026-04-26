/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:41:38 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/25 18:44:51 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_hook(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int	do_collect(t_game *game, int nx, int ny)
{
	char	c;

	c = game->map.grid[ny][nx];
	if (c == '1')
		return (0);
	if (c == 'C')
	{
		game->collected++;
		game->map.grid[ny][nx] = '0';
	}
	if (c == 'E' && game->collected < game->map.nb_collect)
		return (0);
	return (1);
}

void	move_player(t_game *game, int nx, int ny)
{
	int	ox;
	int	oy;

	ox = game->map.p_x;
	oy = game->map.p_y;
	game->map.grid[oy][ox] = '0';
	game->map.grid[ny][nx] = 'P';
	game->map.p_x = nx;
	game->map.p_y = ny;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	draw_tile(game, &game->floor[floor_mask(&game->map, ox, oy)], ox, oy);
	draw_tile(game, &game->player[floor_mask(&game->map, nx, ny)], nx, ny);
}

void	handle_move(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	char	target;

	nx = game->map.p_x + dx;
	ny = game->map.p_y + dy;
	target = game->map.grid[ny][nx];
	if (!do_collect(game, nx, ny))
		return ;
	move_player(game, nx, ny);
	if (target == 'E')
		close_hook(game);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_hook(game);
	if (keycode == KEY_W || keycode == KEY_UP)
		handle_move(game, 0, -1);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		handle_move(game, 0, 1);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		handle_move(game, -1, 0);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		handle_move(game, 1, 0);
	return (0);
}
