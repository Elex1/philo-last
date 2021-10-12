/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melghoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:18:20 by melghoud          #+#    #+#             */
/*   Updated: 2021/10/08 15:24:16 by melghoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str, int *num)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			number = number * 10 + (str[i] - '0');
		else
			return (1);
		i++;
	}
	if (number > 2147483647)
		return (1);
	*num = number;
	return (0);
}

int	philo_died(t_philo *philo, t_data *data, int *baraka, int *i)
{
	pthread_mutex_lock(&(philo->eating));
	if (philo->is_eating == 0)
	{
		if (time_now() - philo->last_time_eat
			> (unsigned int)data->time_to_die)
			watB3(philo, 4, time_now());
	}
	pthread_mutex_unlock(&(philo->eating));
	if (data->die)
		return (1);
	if (data->number_of_meals != 0 && (philo->number_of_eat
			>= data->number_of_meals))
		*baraka += 1;
	(*i)++;
	return (0);
}

void	supervisor(t_data *data)
{
	int			i;
	t_philo		*philo;
	int			baraka;

	while (1)
	{
		baraka = 0;
		i = 0;
		while (i < data->number_of_philosophers)
		{
			philo = (data->philos + i);
			if (philo_died(philo, data, &baraka, &i))
				break ;
		}
		if (baraka == data->number_of_philosophers)
		{
			pthread_mutex_lock(&(data->print));
			data->die = 1;
			pthread_mutex_unlock(&(data->print));
		}
		if (data->die)
			break ;
		usleep(100);
		i = 0;
	}
}

int	kon_fayakon(t_data *data)
{
	if (lancer(data, 0) == 0)
		return (0);
	usleep(100);
	if (lancer(data, 1) == 0)
		return (0);
	return (1);
}
