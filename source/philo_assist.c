/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_assist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:08:26 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/20 01:27:38 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		count;
	char		*dst_dst;
	const char	*src_src;

	count = 0;
	dst_dst = (char *)dst;
	src_src = (const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (count < n)
	{
		dst_dst[count] = src_src[count];
		count++;
	}
	return (dst);
}

char	*philo_strdup(char *s1)
{
	size_t	s_len;
	char	*s2;

	s_len = ft_strlen(s1) + 1;
	s2 = malloc(s_len);
	if (s2 == NULL)
		return (NULL);
	return ((char *)ft_memcpy(s2, s1, s_len));
}

int	philo_atoi(const char *str)
{
	int	the_sign;
	int	the_integer;

	the_sign = 1;
	the_integer = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f')
	{
		str++;
	}
	if (*str == '-')
	{
		the_sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		the_integer = the_integer * 10 + (*str - '0');
		str++;
	}
	if (*str == '\0' && the_integer == 0)
		return (0);
	return (the_integer * the_sign);
}
