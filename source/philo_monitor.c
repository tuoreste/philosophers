/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 23:54:23 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/20 01:28:02 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_return(char *str)
{
	printf(RED "Error:\n%s!\n" RESET, str);
	return (0);
}

int	dying_status(t_data *data)
{
	pthread_mutex_lock(&data->one_dead);
	if (data->count_dead)
	{
		pthread_mutex_unlock(&data->one_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->one_dead);
	return (0);
}

int	finishing_status(t_data *data)
{
	pthread_mutex_lock(&(data->fini_status));
	if (data->one_finished)
	{
		pthread_mutex_unlock(&(data->fini_status));
		return (1);
	}
	pthread_mutex_unlock(&(data->fini_status));
	return (0);
}

void	subvise(t_data *data)
{
	pthread_mutex_lock(&data->fini_status);
	data->one_finished = 1;
	pthread_mutex_unlock(&data->fini_status);
	printf(MAGENTA "%lld %s\n", current_time() - data->start_eating,
		"DONE!!" RESET);
}

void	*supervise(void *args)
{
	int		i;
	t_data	*data;

	data = (t_data *)args;
	while (!finishing_status(data) && !dying_status(data))
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&data->philo[i].eating_mutex);
			if ((current_time() - data->philo[i].last_eat) >= data->death_clock)
			{
				pthread_mutex_unlock(&data->philo[i].eating_mutex);
				declare_dead(data, &data->philo[i]);
				break ;
			}
			pthread_mutex_unlock(&data->philo[i++].eating_mutex);
		}
		if (end_eating(data))
		{
			subvise(data);
			break ;
		}
	}
	return (exiting(data));
}
