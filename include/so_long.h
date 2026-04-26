/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:42:18 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/25 19:02:18 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "libft.h"

# define TILE		64
# define EVT_KEYPRESS	2
# define EVT_DESTROY	17
# define EVT_CLIENT	33
# define MASK_KEYPRESS	1L
# define MASK_STRUCT	131072
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define TEX_WALL	"textures/wall.xpm"
# define TEX_FLOOR	"textures/floor_"
# define TEX_PLAYER	"textures/player_"
# define TEX_COLLECT	"textures/collect_"
# define TEX_EXIT	"textures/exit_"
# define FLOOR_VARIANTS	16

typedef struct s_img
{
	void	*ptr;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		nb_collect;
	int		p_x;
	int		p_y;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	wall;
	t_img	floor[FLOOR_VARIANTS];
	t_img	player[FLOOR_VARIANTS];
	t_img	collect[FLOOR_VARIANTS];
	t_img	exit_img[FLOOR_VARIANTS];
	int		moves;
	int		collected;
}	t_game;

void	error_exit(char *msg);
void	free_game(t_game *game);
void	free_map(char **grid);
char	*read_file(char *path);
int		count_lines(char *buf);
char	*get_line(char *buf, int *pos);
char	**read_map(char *path);
void	parse_row(t_game *game, int i);
void	parse_map(t_game *game);
int		is_wall(t_map *map, int x, int y);
int		floor_mask(t_map *map, int x, int y);
void	load_set(t_game *game, char *base, t_img *arr);
void	draw_cell(t_game *game, int j, int i);
void	free_textures(t_game *game);
void	check_row(t_game *game, int i, int *p, int *e);
void	check_chars(t_game *game);
void	check_walls(t_game *game);
void	check_map(t_game *game);
char	**copy_grid(t_game *game);
void	flood_fill(char **grid, int x, int y);
void	check_path_valid(t_game *game);
int		init_mlx(t_game *game);
t_img	load_tex(t_game *game, char *path);
void	load_textures(t_game *game);
void	draw_tile(t_game *game, t_img *img, int x, int y);
void	render_map(t_game *game);
int		do_collect(t_game *game, int nx, int ny);
void	move_player(t_game *game, int nx, int ny);
void	handle_move(t_game *game, int dx, int dy);
int		key_hook(int keycode, t_game *game);
int		close_hook(t_game *game);

#endif
