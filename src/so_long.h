/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:07:47 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/13 18:29:24 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_sprite
{
	char	**sprite;
}				t_sprite

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos

typedef struct	s_capacity
{
	char		*name;
	t_sprite	*sprite;
	char		*img;
	int			dmg;
}				t_capacity

typedef struct	s_player
{
	char		*name;
	char		*img;
	int			life;
	int			lifemax;
	t_sprite	*dos;
	t_sprite	*face;
	t_sprite	*droite;
	t_sprite	*gauche;
	t_pos		*pos;
	t_capacity	*spell1;
}				t_player

typedef	struct	s_map
{
	char		**map;
	int			move;
	int			xmax;
	int			ymax;
	t_player	**player;
	t_monstre	**monstre;
	t_case		*dirt;
	t_case		*mur;
	t_case		**coin;
	t_case		*exit;
}				t_map

typedef struct	s_case
{
	t_sprite	bg;
	t_sprite	elem;
}				t_case

typedef	struct	s_monstre
{
	char		*name;
	char		*img;
	int			life;
	int			lifemax;
	t_sprite	*dos;
	t_sprite	*face;
	t_sprite	*droite;
	t_sprite	*gauche;
	t_pos		*pos;
	t_capacity	*spell1;	
}				t_monstre

char	*get_next_line(int fd);
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
