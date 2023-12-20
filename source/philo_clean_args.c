/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otuyishi <otuyishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 23:51:50 by otuyishi          #+#    #+#             */
/*   Updated: 2023/12/20 01:27:55 by otuyishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
