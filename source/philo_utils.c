/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:38:36 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/20 01:28:20 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_calloc(size_t count, size_t size)
{
	void	*allocated_m;

	allocated_m = malloc(count * size);
	if (!allocated_m)
	{
		return (NULL);
	}
	ft_bzero(allocated_m, count * size);
	return (allocated_m);
}

long long	current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	*exiting(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
		pthread_mutex_unlock(data->philo[i++].right_fork);
	return (NULL);
}

int	end_eating(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!data->times_eaten)
	{
		return (0);
	}
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&(data->philo[i].eating_mutex));
		if (data->philo[i].n_eat >= data->times_eaten)
			n++;
		pthread_mutex_unlock(&(data->philo[i].eating_mutex));
		i++;
	}
	if (data->n_philos == n)
		return (1);
	return (0);
}

void	declare_dead(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->one_dead);
	printf(RED"%lld %d %s\n", current_time() - data->start_eating,
		philo->id, " died"RESET);
	data->count_dead = 1;
	pthread_mutex_unlock(&data->one_dead);
}
