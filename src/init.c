/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:54:29 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/09 19:55:55 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	init_sprite_monster(t_game *game, t_sprite *sprite)
{
	sprite->slimef = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimef0.xpm", &sprite->w, &sprite->h);
	sprite->slimer[0] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimer0.xpm", &sprite->w, &sprite->h);
	sprite->slimer[1] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimer1.xpm", &sprite->w, &sprite->h);
	sprite->slimer[2] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimer2.xpm", &sprite->w, &sprite->h);
	sprite->slimer[3] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimer3.xpm", &sprite->w, &sprite->h);
	sprite->slimel[0] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimel0.xpm", &sprite->w, &sprite->h);
	sprite->slimel[1] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimel1.xpm", &sprite->w, &sprite->h);
	sprite->slimel[2] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimel2.xpm", &sprite->w, &sprite->h);
	sprite->slimel[3] = mlx_xpm_file_to_image(game->mlx,
			"./assets/monstre/slimel3.xpm", &sprite->w, &sprite->h);
}

void	init_sprite_player(t_game *game, t_sprite *sprite)
{
	sprite->playerf[0] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerface1.xpm", &sprite->w, &sprite->h);
	sprite->playerf[1] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerface2.xpm", &sprite->w, &sprite->h);
	sprite->playerb[0] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerback1.xpm", &sprite->w, &sprite->h);
	sprite->playerb[1] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerback2.xpm", &sprite->w, &sprite->h);
	sprite->playerl[0] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerleft1.xpm", &sprite->w, &sprite->h);
	sprite->playerl[1] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerleft2.xpm", &sprite->w, &sprite->h);
	sprite->playerr[0] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerright1.xpm", &sprite->w, &sprite->h);
	sprite->playerr[1] = mlx_xpm_file_to_image(game->mlx,
			"./assets/player/playerright2.xpm", &sprite->w, &sprite->h);
}

t_sprite	*init_sprite(t_game *game)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite == NULL)
		exit (1);
	sprite->w = 32;
	sprite->h = 32;
	sprite->exit = mlx_xpm_file_to_image(game->mlx,
			"./assets/terrain/exit.xpm", &sprite->w, &sprite->h);
	sprite->move = mlx_xpm_file_to_image(game->mlx,
			"./assets/other/move.xpm", &sprite->w, &sprite->h);
	sprite->coin = mlx_xpm_file_to_image(game->mlx,
			"./assets/other/coin.xpm", &sprite->w, &sprite->h);
	sprite->wall = mlx_xpm_file_to_image(game->mlx,
			"./assets/terrain/rock.xpm", &sprite->w, &sprite->h);
	sprite->background = mlx_xpm_file_to_image(game->mlx,
			"./assets/terrain/grass.xpm", &sprite->w, &sprite->h);
	init_sprite_monster(game, sprite);
	init_sprite_player(game, sprite);
	return (sprite);
}
