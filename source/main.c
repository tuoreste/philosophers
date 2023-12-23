/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 23:43:36 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/23 05:03:25 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_init(t_data *data)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->fini_status, NULL);
	pthread_mutex_init(&data->one_dead, NULL);

}

void	mutex_destroy_and_free(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->fini_status);
	pthread_mutex_destroy(&data->one_dead);
	free(data->philo->array);
	free (data->philo);
	free (data);
}

void	*fill(char **elems, t_data *data)
{
	data->death_clock = philo_atoi(elems[1]);
	data->eat_clock = philo_atoi(elems[2]);
	data->sleep_clock = philo_atoi(elems[3]);
	data->n_eat = 0;
	return (data);
}

/*
FUNCTION LETS_GO
1. Declares data struct containing the var we will need
2. Allocates memory to the whole data struct
3. Data var n_philos is given its arg as a num(in this case num of philos)
4. Through data struct we allocate memo of philo struct based on num of philos
5. protected in case the memo allocation does not work since data is allocated
   as well we immediately free data right before we return
6. Feed args values to vars death,eat,sleep clocks and times eaten as zero in
   in case the arg has not been given.
7. Initiate thread mutex for printing
8. func call init_philos with pass of current data struct records
*/
void	lets_go(char **elems)
{
	int		i;
	t_data	*data;

	data = philo_calloc(sizeof(t_data), 1);
	data->n_philos = philo_atoi(elems[0]);
	data->philo = philo_calloc(sizeof(t_philo), data->n_philos);
	if (!data->philo)
		return (free(data));
	fill(elems, data);
	if (elems[4])
		data->n_eat = philo_atoi(elems[4]);
	mutex_init(data);
	init_philos(data);
	if (pthread_create(&data->check, NULL, supervise, data) != 0)
	{
		error_return("Second thread creation error");
		mutex_destroy_and_free(data);
		return ;
	}
	pthread_join(data->check, NULL);
	i = 0;
	while (i < data->n_philos)
		pthread_join(data->philo[i++].tid, NULL);
	mutex_destroy_and_free(data);
}

/*
MAIN
1.Declares an array called elems that will contain all arguments
2.
  2.1 Checks if arguments are either 2,5 or 6
		2.1.1 the array elems gets the cleaned arguments(eligible args)
		2.1.2 lets_go function takes the array to start the war
		2.1.3 Ofcourse we free the memory we have been using of elems.
  2.2 the number of arguments given are more or not enough so returns an error
*/
int	main(int argc, char **argv)
{
	char	**elems;

	if (argc == 2 || argc == 5 || argc == 6)
	{
		elems = clean_args(argc, argv);
		if (!elems)
			return (1);
		else
		{
			lets_go(elems);
			free_all(elems);
		}
	}
	else
		error_return("In number of inputs");
	return (0);
}
