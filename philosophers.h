/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:27:26 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/10 15:21:13 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		tid;
	long long		last_eat;
	int				time;
	int				id;
	int				n_eat;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eating_mutex;

}		t_philo;

typedef struct s_data
{
	pthread_mutex_t	print;
	long long		start_eating;
	int				n_philos;
	int				death_clock;
	int				eat_clock;
	int				sleep_clock;
	int				times_eaten;
	struct s_philo	*philo;
}		t_data;

//================philosophers.c==================
void	error_exit(char *s);
// void	timestamp(int time, int x, char *s);
char	**clean_args(int argc, char **argv);

//================philo_utils.c===================
int		ft_atoi(const char *str);

#endif
