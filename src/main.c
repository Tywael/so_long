/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:39:53 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/13 15:18:37 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "so_long.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	**map;

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
	map = read_map(fd);
	if (ft_putstr(map_checker(map)))
		return (0);
	if (map == NULL)
		return (0);
	while (*map != NULL)
		printf("%s\n", *(map++));
}
