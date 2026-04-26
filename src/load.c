/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:22:14 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/25 18:39:18 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	load_tex(t_game *game, char *path)
{
	t_img	img;
	int		w;
	int		h;

	img.ptr = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!img.ptr)
		error_exit("Cannot load texture");
	return (img);
}

void	load_set(t_game *game, char *base, t_img *arr)
{
	char	*num;
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (i < FLOOR_VARIANTS)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin(base, num);
		path = ft_strjoin(tmp, ".xpm");
		arr[i] = load_tex(game, path);
		free(num);
		free(tmp);
		free(path);
		i++;
	}
}

void	load_textures(t_game *game)
{
	game->wall = load_tex(game, TEX_WALL);
	load_set(game, TEX_FLOOR, game->floor);
	load_set(game, TEX_PLAYER, game->player);
	load_set(game, TEX_COLLECT, game->collect);
	load_set(game, TEX_EXIT, game->exit_img);
}
