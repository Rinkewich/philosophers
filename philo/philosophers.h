/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:41:04 by fardath           #+#    #+#             */
/*   Updated: 2022/06/16 17:44:39 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MANY_ARGUMENTS 42
# define WRONG_PARAMETER 55
# define MALLOC_PROBLEM 76
# define PTHREAD_ERROR 89

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	OVER,
}				t_action;

typedef struct s_philosopher
{
	int				position;
	int				l_fork;
	int				r_fork;
	int				meals;
	int				eating;
	int				last_meal;
	int				threshold;
	struct s_rules	*parameter;
}				t_philosopher;

typedef struct s_rules
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meals;
	int				finished;
	int				*fork;
	t_philosopher	*philosophers;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*frks_mutexes;
	pthread_mutex_t	die_mutex;
}		t_rules;

int		init_mutex(t_rules *parameter);
int		init_philo(t_rules *parameter);
int		init_param(t_rules *parameter, int argc, const char **argv);
int		init_pthread(t_rules *parameter);
int		ft_atoi(const char *str);
int		ft_error(int error);
int		get_time(void);
int		clear(t_rules *parameter);
void	ft_log(t_philosopher *philo, int timestamp, int action);
void	ft_usleep(int ms);
void	*what_do(void *param);
#endif