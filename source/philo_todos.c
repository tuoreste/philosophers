/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_todos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 23:49:17 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/23 16:43:05 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("get time of day error");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!dying_status(philo->data) && !finishing_status(philo->data))
		printf("%lld %d %s\n", current_time() - philo->data->start_eating,
			philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
}

void	eat_sleep_think(t_philo *philo)
{
	print(philo, " is eating");
	pthread_mutex_lock(&philo->eating_mutex);
	philo->times_eaten++;
	philo->last_eat = current_time();
	pthread_mutex_unlock(&philo->eating_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_usleep(philo->data->eat_clock);
	print(philo, " is sleeping");
	ft_usleep(philo->data->sleep_clock);
	print(philo, " is thinking");
}
