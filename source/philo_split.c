/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:05:21 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/20 01:28:08 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c_s;
	size_t	count1;
	size_t	count2;

	count1 = 0;
	count2 = 0;
	if (!s || start >= ft_strlen(s))
		return (philo_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	c_s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!c_s)
		return (NULL);
	while (s[count1] && count2 < len)
	{
		if (count1 >= start)
		{
			c_s[count2] = s[count1];
			count2++;
		}
		count1++;
	}
	c_s[count2] = 0;
	return (c_s);
}

int	ft_number_of_words(char const *str, char c)
{
	int	iter;
	int	count;

	iter = 0;
	count = 0;
	while (str[iter] != '\0')
	{
		if (str[iter] != c)
		{
			count++;
			while (str[iter] && str[iter] != c)
				iter++;
			if (str[iter] == '\0')
				return (count);
		}
		iter++;
	}
	return (count);
}

void	free_all(char **word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		free(word[i]);
		i++;
	}
	free(word);
}

int	ft_split_loop(char const *str, char c, char **word)
{
	int	iter;
	int	len;

	iter = 0;
	while (*str)
	{
		if (*str != c)
		{
			len = 0;
			while (*str && *str != c && ++len)
				++str;
			word[iter] = ft_substr(str - len, 0, len);
			if (!word[iter])
			{
				free_all(word);
				return (0);
			}
			++iter;
			if (*str == '\0')
				break ;
		}
		++str;
	}
	word[iter] = 0;
	return (1);
}

char	**philo_split(char *str, char c)
{
	char	**word;
	int		res;

	word = (char **)malloc(sizeof(char *) * (ft_number_of_words(str, c) + 1));
	if (word == NULL)
		return (0);
	res = ft_split_loop(str, c, word);
	if (res == 0)
		return (NULL);
	return (word);
}
