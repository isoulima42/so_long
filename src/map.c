/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:38:22 by isoulima          #+#    #+#             */
/*   Updated: 2026/04/24 14:33:18 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

char	*read_file(char *path)
{
	int		fd;
	char	*buf;
	char	*line;
	char	*new;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open map file");
	buf = get_next_line(fd);
	if (!buf)
		error_exit("Empty map file");
	line = get_next_line(fd);
	while (line)
	{
		new = ft_strjoin(buf, line);
		free(buf);
		free(line);
		if (!new)
			error_exit("Memory error");
		buf = new;
		line = get_next_line(fd);
	}
	close(fd);
	return (buf);
}

int	count_lines(char *buf)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && buf[i - 1] != '\n')
		count++;
	return (count);
}

char	*get_line(char *buf, int *pos)
{
	int		start;
	int		len;
	char	*line;

	start = *pos;
	len = 0;
	while (buf[*pos] && buf[*pos] != '\n')
	{
		(*pos)++;
		len++;
	}
	if (buf[*pos] == '\n')
		(*pos)++;
	line = malloc(len + 1);
	if (!line)
		error_exit("Memory error");
	ft_memcpy(line, buf + start, len);
	line[len] = '\0';
	return (line);
}

char	**read_map(char *path)
{
	char	*buf;
	char	**grid;
	int		n;
	int		pos;
	int		i;

	buf = read_file(path);
	n = count_lines(buf);
	grid = malloc(sizeof(char *) * (n + 1));
	if (!grid)
		error_exit("Memory error");
	pos = 0;
	i = 0;
	while (i < n)
	{
		grid[i] = get_line(buf, &pos);
		i++;
	}
	grid[n] = NULL;
	free(buf);
	return (grid);
}
