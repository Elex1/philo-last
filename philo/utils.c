/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melghoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:31:17 by melghoud          #+#    #+#             */
/*   Updated: 2021/10/08 15:21:46 by melghoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_data(t_data *data, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1], &(data->number_of_philosophers)))
			return (0);
		if (data->number_of_philosophers == 0)
			return (0);
		if (ft_atoi(argv[2], &(data->time_to_die)))
			return (0);
		if (ft_atoi(argv[3], &(data->time_to_eat)))
			return (0);
		if (ft_atoi(argv[4], &(data->time_to_sleep)))
			return (0);
		data->number_of_meals = 0;
		if (argc == 6)
		{
			if (ft_atoi(argv[5], &(data->number_of_meals)))
				return (0);
			if (data->number_of_meals == 0)
				return (0);
		}
		return (1);
	}
	return (0);
}

unsigned int	time_now(void)
{
	unsigned int	t;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t);
}

int	init(t_data *data)
{
	data->die = 0;
	if (pthread_mutex_init(&(data->print), NULL) != 0)
		return (0);
	data->philos = (t_philo *)malloc(sizeof(t_philo)
			* data->number_of_philosophers);
	data->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* data->number_of_philosophers);
	if (!data->philos || !data->threads)
		return (0);
	data->begin = time_now();
	return (1);
}

int	initialisation(t_data *data)
{
	int			i;
	t_philo		*philo;

	if (init(data) == 0)
		return (0);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		philo = data->philos + i;
		philo->index = i + 1;
		philo->number_of_eat = 0;
		philo->time_to_sleep = data->time_to_sleep;
		philo->time_to_eat = data->time_to_eat;
		philo->is_eating = 0;
		philo->begin = &(data->begin);
		philo->die = &(data->die);
		if (pthread_mutex_init(&(philo->lfork), NULL) != 0)
			return (0);
		if (pthread_mutex_init(&(philo->eating), NULL) != 0)
			return (0);
		philo->rfork = &((data->philos + ((i + 1)
						% data->number_of_philosophers))->lfork);
		philo->print = &(data->print);
	}
	return (1);
}

int	lancer(t_data *data, int j)
{
	t_philo		*philo;
	int			i;

	i = j;
	while (i < data->number_of_philosophers)
	{
		philo = data->philos + i;
		philo->last_time_eat = data->begin;
		if (pthread_create(data->threads + i,
				NULL, routine, data->philos + i) != 0)
			return (0);
		i += 2;
	}
	return (1);
}
