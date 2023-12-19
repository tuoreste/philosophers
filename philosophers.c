/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:30:10 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/19 04:04:31 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	*philo_calloc(size_t count, size_t size)
{
	void	*allocated_m;

	allocated_m = malloc(count * size);
	if (!allocated_m)
	{
		return (NULL);
	}
	ft_bzero(allocated_m, count * size);
	return (allocated_m);
}

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		count;
	char		*dst_dst;
	const char	*src_src;

	count = 0;
	dst_dst = (char *)dst;
	src_src = (const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (count < n)
	{
		dst_dst[count] = src_src[count];
		count++;
	}
	return (dst);
}

char	*philo_strdup(char *s1)
{
	size_t	s_len;
	char	*s2;

	s_len = ft_strlen(s1) + 1;
	s2 = malloc(s_len);
	if (s2 == NULL)
		return (NULL);
	return ((char *)ft_memcpy(s2, s1, s_len));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c_s;
	size_t	count1;
	size_t	count2;

	count1 = 0;
	count2 = 0;
	if (!s || start >= ft_strlen(s))
		return (philo_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	c_s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!c_s)
		return (NULL);
	while (s[count1] && count2 < len)
	{
		if (count1 >= start)
		{
			c_s[count2] = s[count1];
			count2++;
		}
		count1++;
	}
	c_s[count2] = 0;
	return (c_s);
}

static int	ft_number_of_words(char const *str, char c)
{
	int	iter;
	int	count;

	iter = 0;
	count = 0;
	while (str[iter] != '\0')
	{
		if (str[iter] != c)
		{
			count++;
			while (str[iter] && str[iter] != c)
				iter++;
			if (str[iter] == '\0')
				return (count);
		}
		iter++;
	}
	return (count);
}

void	free_all(char **word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		free(word[i]);
		i++;
	}
	free(word);
}

int	ft_split_loop(char const *str, char c, char **word)
{
	int	iter;
	int	len;

	iter = 0;
	while (*str)
	{
		if (*str != c)
		{
			len = 0;
			while (*str && *str != c && ++len)
				++str;
			word[iter] = ft_substr(str - len, 0, len);
			if (!word[iter])
			{
				free_all(word);
				return (0);
			}
			++iter;
			if (*str == '\0')
				break ;
		}
		++str;
	}
	word[iter] = 0;
	return (1);
}

char	**philo_split(char *str, char c)
{
	char	**word;
	int		res;

	word = (char **)malloc(sizeof(char *) * (ft_number_of_words(str, c) + 1));
	if (word == NULL)
		return (0);
	res = ft_split_loop(str, c, word);
	if (res == 0)
		return (NULL);
	return (word);
}

int	error_return(char *str)
{
	printf(RED "Error:\n%s!\n" RESET, str);
	return (0);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**two_args(char **elems)
{
	int	k;

	k = 0;
	if (elems)
	{
		while (elems[k] != NULL)
		{
			if (!is_valid_number(elems[k - 1]))
			{
				free(elems);
				error_return("Input contains an invalid character");
				return (NULL);
			}
			k++;
		}
		if (k < 4 || k > 5)
		{
			free(elems);
			error_return("In number of inputs");
			return (NULL);
		}
	}
	return (elems);
}

char	**five_or_six_args(int argc, char **argv, char **elems)
{
	int	i;

	if (!elems)
		return (0);
	i = 1;
	while (i < argc)
	{
		elems[i - 1] = philo_strdup(argv[i]);
		if (!elems[i - 1])
		{
			free(elems);
			return (NULL);
		}
		if (!is_valid_number(elems[i - 1]))
		{
			free(elems);
			error_return("Input contains an invalid character");
			return (NULL);
		}
		i++;
	}
	elems[i - 1] = NULL;
	return (elems);
}

char	**clean_args(int argc, char **argv)
{
	char	**elems;

	if (argc == 2)
	{
		elems = philo_split(argv[1], ' ');
		if (!elems)
			return (NULL);
		if (!two_args(elems))
		{
			free(elems);
			return (NULL);
		}
	}
	else if (argc == 5 || argc == 6)
	{
		elems = (char **)philo_calloc(sizeof(char *), argc + 1);
		if (!five_or_six_args(argc, argv, elems))
			return (NULL);
	}
	else
		return (NULL);
	return (elems);
}

int	philo_atoi(const char *str)
{
	int	the_sign;
	int	the_integer;

	the_sign = 1;
	the_integer = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f')
	{
		str++;
	}
	if (*str == '-')
	{
		the_sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		the_integer = the_integer * 10 + (*str - '0');
		str++;
	}
	if (*str == '\0' && the_integer == 0)
		return (0);
	return (the_integer * the_sign);
}

void	close_philo(t_data *data)
{
	free(&data->philo);
	free(&data);
	return ;
}

long long	current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int	dying_status(t_data *data)
{
	pthread_mutex_lock(&data->one_dead);
	if (data->count_dead)
	{
		pthread_mutex_unlock(&data->one_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->one_dead);
	return (0);
}

int	finishing_status(t_data *data)
{
	pthread_mutex_lock(&(data->fini_status));
	if (data->one_finished)
	{
		pthread_mutex_unlock(&(data->fini_status));
		return (1);
	}
	pthread_mutex_unlock(&(data->fini_status));
	return (0);
}

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!dying_status(philo->data) && !finishing_status(philo->data))
		printf("%lld %d %s\n", current_time() - philo->data->start_eating,
			philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	*exiting(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
		pthread_mutex_unlock(data->philo[i++].right_fork);
	return (NULL);
}

int	end_eating(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!data->times_eaten)
	{
		return (0);
	}
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&(data->philo[i].eating_mutex));
		if (data->philo[i].n_eat >= data->times_eaten)
			n++;
		pthread_mutex_unlock(&(data->philo[i].eating_mutex));
		i++;
	}
	if (data->n_philos == n)
		return (1);
	return (0);
}

void	subvise(t_data *data)
{
	pthread_mutex_lock(&data->fini_status);
	data->one_finished = 1;
	pthread_mutex_unlock(&data->fini_status);
}

void	*supervise(void *args)
{
	int		i;
	t_data	*data;

	data = (t_data *)args;
	while (!finishing_status(data) && !dying_status(data))
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&data->philo[i].eating_mutex);
			if ((current_time() - data->philo[i].last_eat) >= data->death_clock)
			{
				pthread_mutex_unlock(&data->philo[i].eating_mutex);
				pthread_mutex_lock(&data->one_dead);
				printf("%lld %d %s\n", current_time() - data->start_eating,
					data->philo[i].id, " died");
				data->count_dead = 1;
				pthread_mutex_unlock(&data->one_dead);
				break ;
			}
			pthread_mutex_unlock(&data->philo[i++].eating_mutex);
		}
		if (end_eating(data))
		{
			subvise(data);
			printf(MAGENTA "%lld %s\n", current_time() - data->start_eating,
				"DONE!!" RESET);
			break ;
		}
	}
	exiting(data);
	return (data);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
}

int	scan(t_philo *philo)
{
	if (!philo->data->times_eaten)
		return (0);
	pthread_mutex_lock(&(philo->eating_mutex));
	if (philo->n_eat == philo->data->times_eaten)
	{
		pthread_mutex_unlock(&(philo->eating_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->eating_mutex));
	return (0);
}

void	eat_sleep_think(t_philo *philo)
{
	print(philo, " is eating");
	philo->n_eat++;
	pthread_mutex_lock(&philo->eating_mutex);
	philo->last_eat = current_time();
	pthread_mutex_unlock(&philo->eating_mutex);
	ft_usleep(philo->data->eat_clock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print(philo, " is sleeping");
	ft_usleep(philo->data->sleep_clock);
	print(philo, " is thinking");
}

/*
FUNC THE ROUTIN
1. Declares iteration and struct philos
2. Casts to t_philo all void args collected through create thread for the routin
3.
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
	pthread_create(&data->check, 0, supervise, data);
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
	pthread_join(data->check, 0);
	i = 0;
	while (i < data->n_philos)
		pthread_join(data->philo[i++].tid, 0);
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
	t_data	*data;

	data = philo_calloc(sizeof(t_data), 1);
	data->n_philos = philo_atoi(elems[0]);
	data->philo = philo_calloc(sizeof(t_philo), data->n_philos);
	if (!data->philo)
		return (free(data));
	data->death_clock = philo_atoi(elems[1]);
	data->eat_clock = philo_atoi(elems[2]);
	data->sleep_clock = philo_atoi(elems[3]);
	data->times_eaten = 0;
	if (elems[4])
		data->times_eaten = philo_atoi(elems[4]);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->fini_status, NULL);
	pthread_mutex_init(&data->one_dead, NULL);
	pthread_mutex_init(&data->one_dead, NULL);
	init_philos(data);
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
			free(elems);
		}
	}
	else
		error_return("In number of inputs");
	return (0);
}
