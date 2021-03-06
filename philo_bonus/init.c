/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:54:09 by fardath           #+#    #+#             */
/*   Updated: 2022/06/17 13:18:41 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_semaphore(t_rules *rules)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("mealcheck");
	rules->forks = sem_open("forks", O_CREAT, S_IRWXU, rules->nb_philo);
	rules->writing = sem_open("write", O_CREAT, S_IRWXU, 1);
	rules->meal_check = sem_open("mealcheck", O_CREAT, S_IRWXU, 1);
	if (rules->forks <= 0 || rules->writing <= 0 || rules->meal_check <= 0)
		return (1);
	return (0);
}

int	init_philosophers(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].x_ate = 0;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

int	init_all(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->dieded = 0;
	if (rules->nb_philo < 2 || rules->time_death < 0 || rules->time_eat < 0
		|| rules->time_sleep < 0 || rules->nb_philo > 250)
		return (1);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (1);
	}
	else
		rules->nb_eat = -1;
	if (rules->nb_eat == 1)
		rules->nb_eat++;
	if (init_semaphore(rules))
		return (2);
	init_philosophers(rules);
	return (0);
}
