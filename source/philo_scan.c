/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:33:28 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/23 16:33:59 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	scan(t_philo *philo)
{
	if (!philo->data->n_eat)
		return (0);
	pthread_mutex_lock(&(philo->eating_mutex));
	if (philo->times_eaten == philo->data->n_eat)
	{
		pthread_mutex_unlock(&(philo->eating_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->eating_mutex));
	return (0);
}
