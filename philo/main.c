/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:41:09 by fardath           #+#    #+#             */
/*   Updated: 2022/06/17 12:26:57 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (ft_error(WRONG_PARAMETER));
	if (init_all(&rules, argv))
		return (ft_error(MANY_ARGUMENTS));
	if (start(&rules))
		return (ft_error(PTHREAD_ERROR));
	return (0);
}
