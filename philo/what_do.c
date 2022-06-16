/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:30:45 by fardath           #+#    #+#             */
/*   Updated: 2022/06/16 17:46:44 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fil_dead(t_philosopher *filosof)
{
	if (!filosof->eating && get_time() > filosof->threshold)
	{
		ft_log(filosof, filosof->threshold, DIED);
		pthread_mutex_lock(&filosof->parameter->write_mutex);
		pthread_mutex_unlock(&filosof->parameter->die_mutex);
		return (1);
	}
	return (0);
}

int	take_forks(t_philosopher *filosof)
{
	int	i;
	int	fork;

	i = 0;
	while (i < 2)
	{
		if (fil_dead(filosof))
			return (1);
		if (i == 0)
			fork = filosof->l_fork;
		else
			fork = filosof->r_fork;
		pthread_mutex_lock(&filosof->parameter->frks_mutexes[fork]);
		if (!filosof->parameter->fork[fork])
		{
			ft_log(filosof, get_time(), TAKING_FORK);
			filosof->parameter->fork[fork] = 1;
			i++;
		}
		pthread_mutex_unlock(&filosof->parameter->frks_mutexes[fork]);
	}
	return (0);
}

int	eat(t_philosopher *philo)
{
	philo->eating = 1;
	philo->last_meal = get_time();
	ft_log(philo, philo->last_meal, EATING);
	ft_usleep(philo->parameter->t_eat);
	philo->threshold = philo->last_meal + philo->parameter->t_die;
	philo->eating = 0;
	philo->meals += 1;
	if (philo->parameter->meals > 0 && philo->meals >= philo->parameter->meals)
	{
		pthread_mutex_lock(&philo->parameter->frks_mutexes[philo->l_fork]);
		philo->parameter->fork[philo->l_fork] = 0;
		pthread_mutex_unlock(&philo->parameter->frks_mutexes[philo->l_fork]);
		pthread_mutex_lock(&philo->parameter->frks_mutexes[philo->r_fork]);
		philo->parameter->fork[philo->r_fork] = 0;
		pthread_mutex_unlock(&philo->parameter->frks_mutexes[philo->r_fork]);
		philo->parameter->finished++;
		if (philo->parameter->finished >= philo->parameter->nb_philo)
		{
			pthread_mutex_lock(&philo->parameter->write_mutex);
			pthread_mutex_unlock(&philo->parameter->die_mutex);
		}
		return (1);
	}
	return (0);
}

int	remove_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->parameter->frks_mutexes[philo->l_fork]);
	philo->parameter->fork[philo->l_fork] = 0;
	pthread_mutex_unlock(&philo->parameter->frks_mutexes[philo->l_fork]);
	pthread_mutex_lock(&philo->parameter->frks_mutexes[philo->r_fork]);
	philo->parameter->fork[philo->r_fork] = 0;
	pthread_mutex_unlock(&philo->parameter->frks_mutexes[philo->r_fork]);
	ft_log(philo, philo->last_meal + philo->parameter->t_eat, SLEEPING);
	ft_usleep(philo->parameter->t_sleep);
	if (fil_dead(philo))
		return (1);
	ft_log(philo, philo->last_meal + philo->parameter->t_eat
		+ philo->parameter->t_sleep, THINKING);
	return (0);
}

void	*what_do(void *param)
{
	t_philosopher	*filosof;

	filosof = (t_philosopher *)param;
	filosof->last_meal = get_time();
	filosof->threshold = filosof->last_meal + filosof->parameter->t_die;
	while (1)
	{
		if (take_forks(filosof) || eat(filosof) || remove_forks(filosof))
			break ;
	}
	return (NULL);
}
