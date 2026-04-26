/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 11:23:51 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/25 18:21:47 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_game	*g_game = NULL;

void	error_exit(char *msg)
{
	ft_printf("Error\n%s\n", msg);
	if (g_game)
		free_game(g_game);
	exit(1);
}

void	free_textures(t_game *game)
{
	int	i;

	if (game->wall.ptr)
		mlx_destroy_image(game->mlx, game->wall.ptr);
	i = 0;
	while (i < FLOOR_VARIANTS)
	{
		if (game->floor[i].ptr)
			mlx_destroy_image(game->mlx, game->floor[i].ptr);
		if (game->player[i].ptr)
			mlx_destroy_image(game->mlx, game->player[i].ptr);
		if (game->collect[i].ptr)
			mlx_destroy_image(game->mlx, game->collect[i].ptr);
		if (game->exit_img[i].ptr)
			mlx_destroy_image(game->mlx, game->exit_img[i].ptr);
		i++;
	}
}

void	free_game(t_game *game)
{
	free_map(game->map.grid);
	free_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		len;

	if (argc != 2)
		error_exit("Usage: ./so_long <map.ber>");
	len = (int)ft_strlen(argv[1]);
	if (len < 4 || argv[1][len - 4] != '.'
		|| argv[1][len - 3] != 'b' || argv[1][len - 2] != 'e'
		|| argv[1][len - 1] != 'r')
		error_exit("Map must have .ber extension");
	ft_bzero(&game, sizeof(t_game));
	g_game = &game;
	game.map.grid = read_map(argv[1]);
	parse_map(&game);
	check_map(&game);
	if (!init_mlx(&game))
		error_exit("MLX init failed");
	load_textures(&game);
	render_map(&game);
	mlx_hook(game.win, EVT_KEYPRESS, MASK_KEYPRESS, key_hook, &game);
	mlx_hook(game.win, EVT_DESTROY, MASK_STRUCT, close_hook, &game);
	mlx_hook(game.win, EVT_CLIENT, 0, close_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
