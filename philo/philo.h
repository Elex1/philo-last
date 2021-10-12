/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melghoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 08:45:34 by melghoud          #+#    #+#             */
/*   Updated: 2021/10/09 17:15:00 by melghoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				index;
	unsigned int	last_time_eat;
	int				number_of_eat;
	int				time_to_sleep;
	int				time_to_eat;
	int				is_eating;
	unsigned int	*begin;
	int				*die;
	pthread_mutex_t	lfork;
	pthread_mutex_t	eating;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*print;
}					t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				number_of_meals;
	int				time_to_sleep;
	int				time_to_eat;
	int				die;
	unsigned int	begin;
	pthread_mutex_t	print;
	pthread_t		*threads;
	t_philo			*philos;
}				t_data;

int				get_data(t_data *data, int argc, char **argv);
void			*routine(void *philo_data);
int				kon_fayakon(t_data *data);
void			watB3(t_philo *philo, int action, unsigned int t);
unsigned int	time_now(void);
int				initialisation(t_data *data);
void			supervisor(t_data *data);
int				ft_atoi(char *str, int *num);
int				lancer(t_data *data, int j);

#endif
