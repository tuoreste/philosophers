/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:10 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/10 03:10:43 by otuyishi         ###   ########.fr       */
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
		{
			if (!is_valid_number(elems[k - 1]))
			{
				free(elems);
				error_exit("Input contains an invalid character");
			}
			k++;
		}
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

long long	current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%lld %d %s\n", current_time() - philo->data->start_eating,
		philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");;
}

void	eating(t_philo *philo)
{
	print(philo, " is eating");
	philo->n_eat++;
	pthread_mutex_lock(&philo->eating_mutex);
	philo->last_eat = current_time();
	pthread_mutex_unlock(&philo->eating_mutex);
	sleep(philo->data->eat_clock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	sleep(philo->data->sleep_clock);
}

void	*routin(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if ((philo->id + 1) % 2)
		sleep(1);
	while (1)
	{
		taking_fork(philo);
		eating(philo);
	}
	return (NULL);
}

void	init_philos(t_data *data)
{
	int				i;
	pthread_mutex_t	*array;

	array = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!array)
		return ;
	i = 0;
	while (i < data->n_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].n_eat = 0;
		data->philo[i].data = data;
		data->philo[i].right_fork = &array[i];
		pthread_mutex_init(&array[i], NULL);
		pthread_mutex_init(&data->philo[i].eating_mutex, NULL);
		if (i == data->n_philos - 1)
			data->philo[0].left_fork = &array[i];
		else
			data->philo[i + 1].left_fork = &array[i];
		i++;
	}
	i = 0;
	data->start_eating = current_time();
	data->one_died = 0;
	data->next_turn = 0;
	i = 0;
	while (i < data->n_philos)
	{
		data->philo[i].last_eat = current_time();
		if (pthread_create(&data->philo[i].tid, NULL, routin,
				&(data->philo[i])))
		{
			free(data->philo);
			free(data);
			free(array);
			error_exit("thread creation error");
		}
		i++;
	}
	i = 0;
	while (i < data->n_philos)
		pthread_join(data->philo[i++].tid, NULL);
}

void	lets_go(char **elems)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return ;
	data->n_philos = philo_atoi(elems[0]);
	data->philo = calloc(sizeof(t_philo), data->n_philos);
	if (!data->philo)
		return (free(data));
	pthread_mutex_init(&data->print, NULL);
	data->death_clock = philo_atoi(elems[1]);
	data->eat_clock = philo_atoi(elems[2]);
	data->sleep_clock = philo_atoi(elems[3]);
	data->times_eaten = 0;
	if (elems[4])
		data->times_eaten = philo_atoi(elems[4]);
	init_philos(data);
}

int	main(int argc, char **argv)
{
	char	**elems;

	if (argc == 2 || argc == 5 || argc == 6)
	{
		elems = clean_args(argc, argv);
		lets_go(elems);
	}
	else
		error_exit("Error in number of inputs");
	// free(elems);
	// num_philos = ft_atoi(argv[1]);
	// pthread_create(&thread_1, NULL, &thread_exec, &phil);
	// pthread_join(&thread_1, NULL);
	return (0);
}
