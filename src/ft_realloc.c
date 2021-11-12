/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:15:39 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/12 17:35:07 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		*(((unsigned char *)dst) + i) = *(((unsigned char *)src) + i);
		i++;
	}
	return ((void *)dst);
}

void	*ft_realloc(void *ptr, int len)
{
	void	*ret;
	
	ret = malloc(len);
	if (ret == NULL)
		return (NULL);
	if (!ft_memcpy(ret, ptr, len))
		return (NULL);
	*((char *)ret + len) = 0;
	free(ptr);
	return (ret);
}
