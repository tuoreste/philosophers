/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:10 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/04 16:34:55 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	return (EXIT_FAILURE);
}

void	timestamp(int time, int x, char *s)
{
	if (s == "fork")
		printf("%d %d has taken a fork", time, x);
	else if (s == "eating")
		printf("%d %d is eating", time, x);
	else if (s == "sleeping")
		printf("%d %d is sleeping", time, x);
	else if (s == "thinking")
		printf("%d %d is thinking", time, x);
	else
		printf("%d %d died", time, x);
}

void	clean_args(int argc, char **argv)
{
	int		i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		while (i <= argc)
		{
			if (ft_atoi(argv[i]) != 0)
				i++;
			else
				error_exit("Invalid input");
		}
	}
	else
		error_exit("Wrong no of inputs");
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
	if (pthread_mutex_init(&data->is_dead, NULL))
		return (1);
	if (pthread_mutex_init(&data->lst_time_eating, NULL))
		return (1);
	if (pthread_mutex_init(&data->eating, NULL))
		return (1);
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
}

int	philosophers_initiated(t_philo *phil, t_data *data)
{
	
}

int	put_data(t_philo *phil, t_data *data, char **argv)
{
	phil->num_of_philos = ft_atoi(argv[1]);
	data->death_clock = ft_atoi(argv[2]);
	data->eat_clock = ft_atoi(argv[3]);
	data->sleep_clock = ft_atoi(argv[4]);
	data->all_done_eating = 0;
	data->is_dead = 0;
	//phil->time = manage time;
	if (argv[5])
		data->times_to_eat = ft_atoi(argv[5]);
	else
		data->times_to_eat = 0;
	if (phil->num_of_philos < 1 || phil->num_of_philos > 200 || \
		data->death_clock < 0 || data->eat_clock < 0 || data->sleep_clock < 0)
		error_exit("Try again! input is invalid");
	if (mutex_initiated(&phil, &data) || philosophers_initiated(&phil, &data))
		error_exit("Error initilizing (mutex/threads of philos)");
}

int	lets_go(char **argv)
{
	t_philo		*phil;
	t_data		*data;

	phil = (t_philo *)malloc(sizeof(t_philo));
	if (!phil)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (free(phil), 1);
	put_data(&phil, &data, argv);
	//free_up() t_phil and t_data;
}

int	main(int argc, char **argv)
{
	clean_args(argc, argv);
	lets_go(argv);
	// num_philos = ft_atoi(argv[1]);
	// pthread_create(&thread_1, NULL, &thread_exec, &phil);
	// pthread_join(&thread_1, NULL);
}
