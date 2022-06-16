/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:33:21 by fardath           #+#    #+#             */
/*   Updated: 2022/06/16 17:51:31 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_pthread(t_rules *parameter)
{
	int			i;
	pthread_t	id;

	i = 0;
	pthread_mutex_lock(&parameter->die_mutex);
	while (i < parameter->nb_philo)
	{
		if (pthread_create(&id, NULL, &what_do,
				(void *)&parameter->philosophers[i]))
			return (ft_error(PTHREAD_ERROR));
		pthread_detach(id);
		if (parameter->nb_philo % 2)
			ft_usleep(500);
		i++;
	}
	return (0);
}

int	init_mutex(t_rules *parameter)
{
	int	i;

	i = 0;
	parameter->frks_mutexes = malloc(sizeof(pthread_mutex_t)
			* parameter->nb_philo);
	if (!parameter->frks_mutexes)
		return (ft_error(MALLOC_PROBLEM));
	while (i < parameter->nb_philo)
	{
		pthread_mutex_init(&parameter->frks_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&parameter->die_mutex, NULL);
	pthread_mutex_init(&parameter->write_mutex, NULL);
	return (0);
}

int	init_philo(t_rules *parameter)
{
	int	i;

	i = 0;
	parameter->philosophers
		= malloc(sizeof(t_philosopher) * parameter->nb_philo);
	parameter->fork = malloc(sizeof(int) * parameter->nb_philo);
	if (!parameter->fork || !parameter->philosophers)
		return (ft_error(MALLOC_PROBLEM));
	i = 0;
	while (i < parameter->nb_philo)
	{
		parameter->fork[i] = 0;
		parameter->philosophers[i].position = i;
		parameter->philosophers[i].l_fork = i;
		parameter->philosophers[i].r_fork = (i + 1) % parameter->nb_philo;
		parameter->philosophers[i].meals = 0;
		parameter->philosophers[i].eating = 0;
		parameter->philosophers[i].parameter = parameter;
		i++;
	}
	return (0);
}

int	init_param(t_rules *parameter, int argc, const char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_error(MANY_ARGUMENTS));
	parameter->nb_philo = ft_atoi(argv[1]);
	parameter->t_die = ft_atoi(argv[2]);
	parameter->t_eat = ft_atoi(argv[3]);
	parameter->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parameter->meals = ft_atoi(argv[5]);
	else if (argc == 5)
		parameter->meals = -1;
	if (parameter->nb_philo < 2 || parameter->t_die <= 0
		|| parameter->t_eat <= 0 || parameter->t_sleep <= 0
		|| parameter->meals == 0)
		return (ft_error(WRONG_PARAMETER));
	parameter->finished = 0;
	return (0);
}
