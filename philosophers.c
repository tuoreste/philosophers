/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:10 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/05 23:00:41 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

static int	ft_number_of_words(char const *str, char c)
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

static void	free_all(char **word)
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

static int	ft_split_loop(char const *str, char c, char **word)
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

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**two_args(char **elems)
{
	int	k;

	k = 0;
	if (elems)
	{
		k = 0;
		while (elems[k] != NULL)
			k++;
		if (k < 4 || k > 5)
		{
			free(elems);
			error_exit("Error in number of inputs");
		}
	}
	return (elems);
}

char	**five_or_six_args(int argc, char **argv, char **elems)
{
	int	i;

	if (!elems)
		return (0);
	i = 1;
	while (i < argc)
	{
		elems[i - 1] = philo_strdup(argv[i]);
		if (!elems[i - 1])
		{
			free(elems);
			return (NULL);
		}
		if (!is_valid_number(elems[i - 1]))
		{
			free(elems);
			error_exit("Input contains an invalid character");
		}
		i++;
	}
	elems[i - 1] = NULL;
	return (elems);
}

char	**clean_args(int argc, char **argv)
{
	char	**elems;

	if (argc == 2)
	{
		elems = philo_split(argv[1], ' ');
		if (!elems)
			return (NULL);
		two_args(elems);
	}
	else if (argc == 5 || argc == 6)
	{
		elems = (char **)malloc(sizeof(char *) * (argc + 1));
		if (!elems)
			return (NULL);
		five_or_six_args(argc, argv, elems);
	}
	else
		return (NULL);
	return (elems);
}

// void	timestamp(int time, int x, char *s)
// {
// 	if (s == "fork")
// 		printf("%d %d has taken a fork", time, x);
// 	else if (s == "eating")
// 		printf("%d %d is eating", time, x);
// 	else if (s == "sleeping")
// 		printf("%d %d is sleeping", time, x);
// 	else if (s == "thinking")
// 		printf("%d %d is thinking", time, x);
// 	else
// 		printf("%d %d died", time, x);
// }

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

int	mutex_initiated(t_philo *phil, t_data *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* phil->num_of_philos);
	i = 0;
	while (i < phil->num_of_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			error_exit("Error of forks mutex");
		i++;
	}
	if (pthread_mutex_init(&data->all_done_eating, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_status, NULL))
		return (1);
	if (pthread_mutex_init(&data->lst_time_eating, NULL))
		return (1);
	if (pthread_mutex_init(&data->eating, NULL))
		return (1);
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
}

void	*functioning(void *args)
{
}

int	thread_initiated(t_philo *phil, t_data *data)
{
	int	i;

	i = 0;
	while (phil->one_died == 0)
	{
		phil->id = i;
		if (pthread_create(&phil->thread_1, NULL, &functioning,
				(void *)&phil) != 0)
			error_exit("Error creating thread_1");
		i++;
	}
}

int	put_data(t_philo *phil, t_data *data, char **elems)
{
	phil->num_of_philos = ft_atoi(elems[0]);
	data->death_clock = ft_atoi(elems[1]);
	data->eat_clock = ft_atoi(elems[2]);
	data->sleep_clock = ft_atoi(elems[3]);
	phil->one_died = 0;
	// phil->time = manage time;
	if (elems[4])
		data->times_to_eat = ft_atoi(elems[4]);
	else
		data->times_to_eat = 0;
	if (phil->num_of_philos < 1 || phil->num_of_philos > 200
		|| data->death_clock < 0 || data->eat_clock < 0
		|| data->sleep_clock < 0)
		error_exit("Try again! input is invalid");
	if (mutex_initiated(&phil, &data) || thread_initiated(&phil, &data))
		error_exit("Error initilizing (mutex/threads of philos)");
}

int	lets_go(char **elems)
{
	t_philo	*phil;
	t_data	*data;

	phil = (t_philo *)malloc(sizeof(t_philo));
	if (!phil)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (free(phil), 1);
	put_data(&phil, &data, elems);
	// free_up() t_phil and t_data;
}

int	main(int argc, char **argv)
{
	char	**elems;

	if (argc == 2 || argc == 5 || argc == 6)
		elems = clean_args(argc, argv);
	else
		error_exit("Error in number of inputs");
	lets_go(elems);
	//free(elems);
	// num_philos = ft_atoi(argv[1]);
	// pthread_create(&thread_1, NULL, &thread_exec, &phil);
	// pthread_join(&thread_1, NULL);
}
