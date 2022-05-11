/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:38:24 by yalthaus          #+#    #+#             */
/*   Updated: 2022/02/14 15:01:54 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum e_type
{
	monstre = 'M',
	end = 'E',
	player = 'P',
	empty = '0',
	wall = '1',
	coin = 'C'
}				t_type;

typedef struct s_sprite
{
	void	*background;
	void	*exit;
	void	*move;
	void	*playerf[2];
	void	*playerl[2];
	void	*playerr[2];
	void	*playerb[2];
	void	*slimef;
	void	*slimer[4];
	void	*slimel[4];
	void	*coin;
	void	*wall;
	int		w;
	int		h;
}				t_sprite;

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_case
{
	t_sprite	*background;
	t_type		type;
	void		*img;
	t_pos		*pos;
	t_type		old_type;
	int			status;
}				t_case;

typedef struct s_map
{
	char		**map;
	int			move;
	t_sprite	*sprite;
	t_pos		*player_pos;
	t_pos		*monster_pos;
	int			monster_move;
	int			monster_side;
	int			xmax;
	int			ymax;
	int			ncoin;
	t_case		***grid;
}				t_map;

typedef struct s_game
{
	t_map	*map;
	void	*win;
	void	*mlx;
}				t_game;

# define KEY_PRESS 2
# define KEY_EXIT 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_B 11

int			move_monster(t_game *game);
char		*get_next_line(int fd);
char		*ft_itoa(int n);
void		close_game(t_game *game);
void		draw_move(t_game *game);
int			key_press(int keycode, t_game *game);
void		init_game(int fd);
t_sprite	*init_sprite(t_game *game);
int			ft_mapline(t_map *map);
char		*map_checker(char **map);
int			ft_putstr(char *str);
int			exit_checker(char **map);
int			coin_checker(char **map);
int			monster_checker(char **map);
int			ft_extension(char *name, char *ext);
int			ft_isinset(char c, char *set);
void		*ft_realloc(void *ptr, int size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *string);
char		*ft_strdup(const char *src);
char		**read_map(int fd);
void		init_map(t_game *game, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_itoa(int n);
#endif
