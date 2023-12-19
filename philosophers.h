/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:27:26 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/19 03:14:18 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

typedef struct s_philo
{
	pthread_t		tid;
	long long		last_eat;
	int				time;
	int				id;
	int				n_eat;
	int				back;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eating_mutex;
}		t_philo;

typedef struct s_data
{
	pthread_t		check;
	pthread_mutex_t	print;
	pthread_mutex_t	fini_status;
	pthread_mutex_t	one_dead;
	long long		start_eating;
	long long		end_eating;
	int				n_philos;
	int				count_dead;
	int				one_finished;
	int				death_clock;
	int				eat_clock;
	int				sleep_clock;
	int				times_eaten;
	struct s_philo	*philo;
}		t_data;

//================philosophers.c==================
int		error_return(char *str);
// void	timestamp(int time, int x, char *s);
char	**clean_args(int argc, char **argv);

//================philo_utils.c===================

#endif
