/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:10 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/03 17:13:52 by otuyishi         ###   ########.fr       */
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

int	put_data(t_philo *phil, t_data *data, char **argv)
{
	t_data->num_of_philos = ft_atoi(argv[1]);
	t_data.death_clock = argv[2];
	t_data.eat_clock = argv[3];
	t_data.sleep_clock = argv[4];
	t_philo.time = 0;
	t_philo.
	if (argv[5])
		t_data.times_to_eat = argv[5];
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
	free_up();
}

int	main(int argc, char **argv)
{
	clean_args(argc, argv);
	lets_go(argv);
	// num_philos = ft_atoi(argv[1]);
	// pthread_create(&thread_1, NULL, &thread_exec, &phil);
	// pthread_join(&thread_1, NULL);
}
