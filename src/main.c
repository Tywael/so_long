/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:39:53 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/19 14:18:31 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "so_long.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_game	*game;

	if (argc != 2)
		return (0);
	if (ft_extension(*(argv + 1), ".ber"))
	{
		write(1, "extension incorrect", 19);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (0);
	game = init_game(fd);
	if (!game)
		return (0);
	while (game->map->map != NULL)
		printf("%s\n", *(game->map->map++));
}
