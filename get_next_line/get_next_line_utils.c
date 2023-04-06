/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:11:30 by smallem           #+#    #+#             */
/*   Updated: 2023/04/05 16:58:55 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	while (str && *str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (str && *str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	tmp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (tmp == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		tmp[i++] = s2[j++];
	}
	tmp[i] = '\0';
	return (tmp);
}

void	ft_bzero(void *ptr, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)ptr;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}	
}

void	*ft_calloc(size_t nbelem, size_t sizelem)
{
	char	*ptr;

	ptr = (char *)malloc(nbelem * sizelem);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nbelem * sizelem);
	return (ptr);
}
