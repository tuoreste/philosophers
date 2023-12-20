/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:10 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/20 01:28:26 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
FUNC ONE_ROUTINE
1. Takes args of the routine
2. func returns nothing
*/
void	*one_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	return ((void *)0);
}

/*
FUNC ONE_PHILO
1. Creates a simple thread for a routine of one philo of which if not its error
2. Prints out him taking a fork
3. Sleeps
4. Prints his death
5. Announces his death to data struct thru increamenting the count_dead
*/
void	one_philo(t_data *data)
{
	if (pthread_create(&data->philo[0].tid, NULL, &one_routine,
			&data->philo[1]))
	{
		error_return("thread creation error");
		return ;
	}
	print(&data->philo[0], "has taken fork");
	ft_usleep(data->eat_clock);
	print(&data->philo[0], "died");
	data->philo[0].data->count_dead = 1;
	return ;
}

/*
FUNC THE ROUTIN
1. Declares iteration and struct philos
2. Casts to t_philo all void args collected through create thread for the routin
3. Give even ids some sleep as the rest start eating
3. As long as no one is dead and no has finished eating, take forks, eat then
   sleep then think.
*/
void	*routin(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if ((philo->id + 1) % 2)
		ft_usleep(philo->data->eat_clock);
	while (!dying_status(philo->data) && !finishing_status(philo->data))
	{
		taking_fork(philo);
		eat_sleep_think(philo);
	}
	return (philo);
}

/*
FUNC EACH_PHILO
1. Initiates i(iteration) and array to track the table
2. Allocate memo for the array based on the number of the philos
3. while iteration has not reached the last philos do the following
   3.1 philo i receives id from 1 up to number of philos
   3.2 num of eats of each philos initiated at 0
   3.3 each philo receives data vars in the data structure
   3.4 each philo allocates a fork on their right on the table
   3.5 initiates mutex to each philos array position
   3.6 initiates mutex for eating for each philo
   3.7 give access to left fork for the last on table depending on even or odd
*/
void	each_philo(t_data *data)
{
	int				i;
	pthread_mutex_t	*array;

	array = philo_calloc(sizeof(pthread_mutex_t), data->n_philos);
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
}

/*
FUNCTION INIT_PHILOS
1. Declares var i (for iterations) & thread named check
2. Loop thru for as long as the num of philos and do the following
		2.1. pass to philo num[i] the var last_eat as current time we are
		2.2. now create a thread though which we are going to call the routin
				but also tracking each philos id for differenciation of each of
				of the on the table.
				2.2.1
				In case the creation of thread fails, protect to immediately
				free the rest of the allocated memory and exit with an error.
		2.3. Keep increamenting the loop
3. create a thread to call for supervision over the on going calls
4. join the thread's infos
5. check the joining thread status
*/
void	init_philos(t_data *data)
{
	int	i;

	each_philo(data);
	data->start_eating = current_time();
	i = 0;
	while (i < data->n_philos)
	{
		if (data->n_philos == 1)
		{
			one_philo(data);
			return ;
		}
		data->philo[i].last_eat = current_time();
		if (pthread_create(&data->philo[i].tid, 0, routin, &(data->philo[i])))
		{
			error_return("First thread creation failed");
			return ;
		}
		i++;
	}
}
