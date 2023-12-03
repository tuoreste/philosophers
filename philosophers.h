/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:27:26 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/03 16:45:34 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t	philosophe;
	int			time;

}		t_philo;

typedef struct s_data
{
	t_philo		*philo;
	int			num_of_philos;
	int			death_clock;
	int			eat_clock;
	int			sleep_clock;

	int			times_to_eat;

}		t_data;

//================philosophers.c==================
int		error_exit(char *s);
void	timestamp(int time, int x, char *s);
void	clean_args(int argc, char **argv);

//================philo_utils.c===================
int		ft_atoi(const char *str);

#endif
