/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melghoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 08:45:22 by melghoud          #+#    #+#             */
/*   Updated: 2021/10/08 14:13:27 by melghoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!get_data(&data, argc, argv))
		return (0);
	if (!initialisation(&data))
		return (0);
	if (!kon_fayakon(&data))
		return (0);
	supervisor(&data);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(*(data.threads + i), NULL);
		i++;
	}
	free(data.threads);
	free(data.philos);
	return (0);
}
