/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melghoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:21:22 by melghoud          #+#    #+#             */
/*   Updated: 2021/10/09 16:51:36 by melghoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	watB3(t_philo *philo, int action, unsigned int t)
{
	const char	*actions[5] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	pthread_mutex_lock(philo->print);
	if (*(philo->die) == 0)
	{
		printf("%u %d %s\n", t - *(philo->begin), philo->index, actions[action]);
		if (action == 0)
			printf("%u %d %s\n", t - *(philo->begin),
				philo->index, actions[action]);
		if (action == 4)
			(*philo->die) = 1;
	}
	pthread_mutex_unlock(philo->print);
}

void	fi9_bkri(int t, int die)
{
	unsigned int	current_time;

	current_time = time_now();
	if (!die)
	{
		usleep(t * 1000 - 20000);
		while (time_now() - current_time < (unsigned int)t)
			continue ;
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->lfork));
	pthread_mutex_lock(philo->rfork);
	watB3(philo, 0, time_now());
	pthread_mutex_lock(&(philo->eating));
	philo->is_eating = 1;
	philo->last_time_eat = time_now();
	pthread_mutex_unlock(&(philo->eating));
}

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	while (1)
	{
		eating(philo);
		watB3(philo, 1, time_now());
		philo->number_of_eat += 1;
		fi9_bkri(philo->time_to_eat, *(philo->die));
		pthread_mutex_unlock(&(philo->lfork));
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_lock(&(philo->eating));
		philo->is_eating = 0;
		pthread_mutex_unlock(&(philo->eating));
		watB3(philo, 2, time_now());
		fi9_bkri(philo->time_to_sleep, *(philo->die));
		watB3(philo, 3, time_now());
		if (*(philo->die))
			break ;
	}
	return (NULL);
}
