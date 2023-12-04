/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:52 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/12/04 15:22:58 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include <fcntl.h>

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(1);
	return (ptr);
}

int	map_init(t_map *map, char *cub)
{
	map = ft_malloc(sizeof(t_map));
	map->textures = ft_malloc(sizeof(t_textures));
	map->height = get_height(cub);
	map->width = get_width(cub);
}
void	free_split(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	parse_textures(char *line, t_textures *textures)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!ft_strncmp("NO", split[0], 2))
		textures->north = ft_stdrup(split[1]);
	else if (ft_strncmp("EA", split[0], 2))
		textures->east = ft_strdup(split[1]);
	else if (ft_strncmp("SO", split[0], 2))
		textures->south = ft_strdup(split[1]);
	else if (ft_strncmp("WE", split[0], 2))
		textures->west = ft_strdup(split[1]);
	else if (ft_strncmp("F", split[0], 1))
		textures->floor = ft_strdup(split[1]);
	else if (ft_strncmp("C", split[0], 1))
		textures->ceiling = ft_strdup(split[1]);
	free_split(split);
}

void	parse_map(char *line, t_map *map, int i)
{
}


t_map	*parse_cub(char *cub)
{
	t_map		*map;
	int			fd;
	char		*line;
	int			i;

	map_init(map, cub);
	fd = open(cub, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '1')
			parse_textures(line, map->textures);
		else
		{
			parse_map(line, map, i);
			i++;
		}
	}
	close(fd);
}
