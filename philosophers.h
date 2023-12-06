/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:27:26 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/05 16:39:10 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	thread_1;
	int			num_of_philos;
	int			time;
	int			id;
	int			one_died;
}		t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				death_clock;
	int				eat_clock;
	int				sleep_clock;
	int				times_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	all_done_eating;
	pthread_mutex_t	death_status;
	pthread_mutex_t	lst_time_eating;
	pthread_mutex_t	eating;
	pthread_mutex_t	print;
}		t_data;

//================philosophers.c==================
void	error_exit(char *s);
// void	timestamp(int time, int x, char *s);
char	**clean_args(int argc, char **argv);

//================philo_utils.c===================
int		ft_atoi(const char *str);

#endif
