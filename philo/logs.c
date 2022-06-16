/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:29:21 by fardath           #+#    #+#             */
/*   Updated: 2022/06/16 17:49:17 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_log(t_philosopher *philo, int timestamp, int action)
{
	pthread_mutex_lock(&philo->parameter->write_mutex);
	if (action == TAKING_FORK)
		printf("%d %d has taken a fork\n", timestamp, philo->position + 1);
	else if (action == EATING)
		printf("%d %d is eating\n", timestamp, philo->position + 1);
	else if (action == SLEEPING)
		printf("%d %d is sleeping\n", timestamp, philo->position + 1);
	else if (action == THINKING)
		printf("%d %d is thinking\n", timestamp, philo->position + 1);
	else if (action == DIED)
		printf("%d %d died\n", timestamp, philo->position + 1);
	pthread_mutex_unlock(&philo->parameter->write_mutex);
}

int	ft_error(int error)
{
	if (error == WRONG_PARAMETER)
		printf("Wrong parameter.\n");
	else if (error == MANY_ARGUMENTS)
		printf("Wrong syntax.\n");
	else if (error == MALLOC_PROBLEM)
		printf("Malloc not good.\n");
	else if (error == PTHREAD_ERROR)
		printf("pthread error.\n");
	return (1);
}
