/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:41:09 by fardath           #+#    #+#             */
/*   Updated: 2022/06/16 17:48:57 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, const char **argv)
{
	t_rules	parameter;

	if (init_param(&parameter, argc, argv)
		|| init_philo(&parameter) || init_mutex(&parameter))
		return (1);
	if (init_pthread(&parameter))
		return (1);
	pthread_mutex_lock(&parameter.die_mutex);
	pthread_mutex_unlock(&parameter.die_mutex);
	clear(&parameter);
	exit(0);
}
