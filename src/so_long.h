/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:07:47 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/26 16:13:02 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>

typedef enum e_type
{
	monstre = 'M',
	player = 'P',
	empty = '0',
	wall = '1',
	coin = 'C'
}				t_type;

typedef struct	s_sprite
{
	void	*sprite;
	int		w;
	int		h;
}				t_sprite;

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_case
{
	void		*content;
	t_sprite	*background;
	t_type		type;
}				t_case;
/*
typedef struct	s_capacity
{
	char		*name;
	t_sprite	*sprite;
	char		*img;
	int			dmg;
}				t_capacity;
*/
typedef struct	s_wall
{
	t_pos		*pos;
	t_sprite	*wall;
}				t_wall;

typedef struct	s_coin
{
	t_pos		*pos;
	int			get;
	t_sprite	*coin[4];
}				t_coin;

typedef struct	s_exit
{
	t_pos		*pos;
	int			open;
	t_sprite	*exit;
}				t_exit;

typedef	struct	s_monstre
{
	char		*name;
	int			life;
	int			lifemax;
	t_sprite	*img[2];
	t_pos		*pos;
}				t_monstre;

typedef struct	s_player
{
	char		*name;
	int			life;
	int			lifemax;
	t_sprite	*back[2];
	t_sprite	*face[2];
	t_sprite	*right[2];
	t_sprite	*left[2];
	t_pos		*pos;
}				t_player;

typedef	struct	s_map
{
	char		**map;
	int			move;
	int			xmax;
	int			ymax;
	int			ncoin;
	t_case		***grid;
}				t_map;

typedef struct	s_game
{
	t_map	*map;
	void	*win;
	void	*mlx;
}				t_game;


char	*get_next_line(int fd);
t_game	*init_game(int fd);
int		ft_mapline(t_map *map);
char	*map_checker(char **map);
int		ft_putstr(char *str);
int		exit_checker(char **map);
int		coin_checker(char **map);
int		ft_extension(char *name, char *ext);
int		ft_isinset(char c, char *set);
void	*ft_realloc(unsigned long ulptr, int size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *string);
char	*ft_strdup(const char *src);
char	**read_map(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

#endif
