/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:29:21 by fardath           #+#    #+#             */
/*   Updated: 2022/06/17 12:25:19 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action_print(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->dieded))
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i %s\n", id + 1, string);
	}
	pthread_mutex_unlock(&(rules->writing));
	return ;
}

int	ft_error(int error)
{
	if (error == WRONG_PARAMETER)
		printf("Wrong parameter.\n");
	else if (error == MANY_ARGUMENTS)
		printf("Wrong syntax.\n");
	else if (error == PTHREAD_ERROR)
		printf("pthread error.\n");
	return (1);
}
