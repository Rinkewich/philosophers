/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardath <fardath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:37:48 by fardath           #+#    #+#             */
/*   Updated: 2022/06/17 13:12:29 by fardath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

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
	pthread_t			death_check;
	pid_t				proc_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	long long			first_timestamp;
	sem_t				*meal_check;
	sem_t				*forks;
	sem_t				*writing;
	t_philosopher		philosophers[250];
}						t_rules;

int			init_semaphore(t_rules *rules);
int			init_philosophers(t_rules *rules);
int			init_all(t_rules *rules, char **argv);
int			ft_error(int error);
int			ft_atoi(const char *str);
int			start(t_rules *rules);
void		action_print(t_rules *rules, int id, char *string);
void		smart_sleep(long long time, t_rules *rules);
void		philo_eats(t_philosopher *philo);
void		*death_checker(void *void_philosopher);
void		p_process(void *void_phil);
void		exit_launcher(t_rules *rules);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
#endif