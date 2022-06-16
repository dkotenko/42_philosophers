/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2022/06/16 20:58:01 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define ERR_MALLOC "Can't allocate memory"
#define ERR_MALLOC_SIZE "Invalid malloc size"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	*ft_memalloc(size_t size)
{
	void	*a;

	if (size + 1 < size)
		handle_error(ERR_MALLOC_SIZE);
	a = malloc(size);
	if (!a)
		handle_error(ERR_MALLOC);
	ft_memset(a, 0, size);
	return (a);
}

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)destination;
	while (n > 0)
	{
		*(s++) = (unsigned char)c;
		n--;
	}
	return (destination);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!n || (!dest && !src))
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char			*dupl;
	unsigned int	len;

	len = ft_strlen(src);
	dupl = ft_memalloc(sizeof(char) * len);
	len = 0;
	while (src[len])
	{
		dupl[len] = src[len];
		len++;
	}
	return (dupl);
}

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)ptr1;
	p2 = (unsigned char *)ptr2;
	i = 0;
	while (i < num && *p1 == *p2)
	{
		i++;
		p1++;
		p2++;
	}
	if (i == num)
		return (0);
	else
		return (*p1 - *p2);
	return (0);
}
