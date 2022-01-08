/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 10:49:44 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/08 17:28:29 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	can_go(int x, int y, t_game *game)
{
	if (game->map->grid[y][x]->type == wall)
		return (0);
	else if (game->map->grid[y][x]->type == monstre)
		exit(1);
	else if (game->map->grid[y][x]->type == coin && game->map->grid[y][x]->status == 0)
	{
		game->map->grid[y][x]->status = 1;
		game->map->ncoin--;
		return (1);
	}
	else if (game->map->grid[y][x]->type == end)
	{
		if (game->map->ncoin == 0)
			exit(0);
		else
			return (0);
	}
	return (1);
}



int	change_type(t_game *game, int x, int y, t_type type)
{
	game->map->grid[y][x]->old_type = game->map->grid[y][x]->type;
	game->map->grid[y][x]->type = type;
	

    return (0);
}

int	sprite_update(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->map->grid[y][x]->background, x * 32, y * 32);
	if (game->map->grid[y][x]->img != NULL && game->map->grid[y][x]->status != 1)
		mlx_put_image_to_window(game->mlx, game->win, game->map->grid[y][x]->img, x * 32, y * 32);
	return (0);
}

int	move_player(int x, int y, t_game *game)
{
	t_case *temp;

	temp = game->map->grid[game->map->player_pos->y][game->map->player_pos->x];
	game->map->grid[game->map->player_pos->y][game->map->player_pos->x] = game->map->grid[y][x];
	game->map->grid[y][x] = temp;
	sprite_update(game, x, y);
	sprite_update(game, game->map->player_pos->x, game->map->player_pos->y);
	game->map->player_pos->x = x;
	game->map->player_pos->y = y;
	return (0);
}

int	player_move(int	keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->map->player_pos->x;
	y = game->map->player_pos->y;
	if (keycode == KEY_A)
		--x;
	else if (keycode == KEY_D)
		++x;
	else if (keycode == KEY_W)
		y--;
	else if (keycode == KEY_S)
		y++;
	if (can_go(x, y, game))
	{
		move_player(x, y, game);
		game->map->move++;
	}
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit (0);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		if (player_move(keycode, game))
			return (1);
	return (0);

}
