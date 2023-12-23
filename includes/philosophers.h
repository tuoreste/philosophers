/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:27:26 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/22 22:42:07 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

typedef struct s_philo
{
	pthread_t		tid;
	long long		last_eat;
	int				time;
	int				id;
	int				eating_rounds;
	int				back;
	int				times_eaten;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	*array;
}					t_philo;

typedef struct s_data
{
	pthread_t		check;
	pthread_mutex_t	print;
	pthread_mutex_t	fini_status;
	pthread_mutex_t	one_dead;
	long long		start_eating;
	long long		end_eating;
	int				n_eat;
	int				n_philos;
	int				count_dead;
	int				one_finished;
	int				death_clock;
	int				eat_clock;
	int				sleep_clock;
	struct s_philo	*philo;
}					t_data;

//================philosophers.c==================
int					main(int argc, char **argv);
void				lets_go(char **elems);
void				*fill(char **elems, t_data *data);
void				mutex_destroy_and_free(t_data *data);
void				mutex_init(t_data *data);
void				init_philos(t_data *data);
void				one_philo(t_data *data);
void				*one_routine(void *args);
void				each_philo(t_data *data);
void				*routin(void *args);
void				eat_sleep_think(t_philo *philo);
void				taking_fork(t_philo *philo);
void				*supervise(void *args);
void				declare_dead(t_data *data, t_philo *philo);
void				subvise(t_data *data);
int					end_eating(t_data *data);
void				*exiting(t_data *data);
void				print(t_philo *philo, char *msg);
int					finishing_status(t_data *data);
int					dying_status(t_data *data);
long long			current_time(void);
int					philo_atoi(const char *str);
char				**clean_args(int argc, char **argv);
char				**five_or_six_args(int argc, char **argv, char **elems);
char				**two_args(char **elems);
int					is_valid_number(char *str);
int					ft_isdigit(int c);
int					error_return(char *str);
char				**philo_split(char *str, char c);
int					ft_split_loop(char const *str, char c, char **word);
void				free_all(char **word);
int					ft_number_of_words(char const *str, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*philo_strdup(char *s1);
void				*ft_memcpy(void *dst, const void *src, size_t n);
size_t				ft_strlen(const char *str);
void				*philo_calloc(size_t count, size_t size);
int					ft_usleep(size_t milliseconds);
size_t				get_current_time(void);
void				ft_bzero(void *s, size_t n);
int					scan(t_philo *philo);

#endif
