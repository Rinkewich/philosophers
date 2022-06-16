/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:35:22 by fardath           #+#    #+#             */
/*   Updated: 2022/06/16 17:43:16 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

void	ft_usleep(int ms)
{
	int	end;

	end = get_time() + ms;
	while (get_time() < end)
		usleep(ms / 1000);
}

int	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	clear(t_rules *parameter)
{
	int	i;

	i = 0;
	while (i < parameter->nb_philo)
	{
		pthread_mutex_destroy(&parameter->frks_mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&parameter->write_mutex);
	pthread_mutex_destroy(&parameter->die_mutex);
	free(parameter->frks_mutexes);
	free(parameter->philosophers);
	free(parameter->fork);
	return (0);
}
