/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:41:04 by fardath           #+#    #+#             */
/*   Updated: 2022/06/17 12:27:04 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define MANY_ARGUMENTS 42
# define WRONG_PARAMETER 55
# define PTHREAD_ERROR 89

typedef struct s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philosopher		philosophers[250];
}						t_rules;

int			init_all(t_rules *rules, char **argv);
int			init_philosophers(t_rules *rules);
int			init_mutex(t_rules *rules);
int			ft_error(int error);
int			ft_atoi(const char *str);
int			ft_error(int error);
int			start(t_rules *rules);
void		action_print(t_rules *rules, int id, char *string);
void		smart_sleep(long long time, t_rules *rules);
void		action_print(t_rules *rules, int id, char *string);
void		philo_eats(t_philosopher *philo);
void		*p_thread(void *void_philosopher);
void		exit_launcher(t_rules *rules, t_philosopher *philos);
void		death_checker(t_rules *r, t_philosopher *p);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
#endif