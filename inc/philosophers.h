/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/16 16:03:42 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include "ft_printf.h"

/* time to eat in microseconds */
# define TIME_TO_EAT 710000

/* time to die in seconds */
# define TIME_TO_DIE 10

/* time to sleep in microseconds */
# define TIME_TO_SLEEP 450000

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct timeval	t_timeval;
typedef struct timezone	t_timezone;

typedef struct s_fork
{
	int				in_use;
	pthread_mutex_t	*fork_mutex;
}					t_fork;

typedef struct s_philo
{
	t_fork			*forks[2];
	size_t			index;
	size_t			n_meals;
	pthread_t		*philo_thread;
	t_timeval		*start_time;
	int				start_time_ms;
	t_timeval		*last_meal;
	t_timezone		*tz;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*start_mutex;
}					t_philo;

typedef struct s_table
{
	t_fork			*forks;
	size_t			n_fed_philos;
	size_t			n_philos;
	t_philo			*philos;
	ssize_t			meal_obj;
	t_timeval		*start_time;
	t_timezone		*tz;
	pthread_mutex_t	*start;
}					t_table;

/* definitely NOT libft :) */

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);
int		ft_iswhitespace(int c);
int		ft_isdigit(int c);

/* ==== ACTIONS.C ==== */

int		take_fork(t_philo *philo, t_fork *fork);
int		drop_fork(t_fork *fork);
int		take_forks(t_philo *philo);
void	philo_log(t_timeval *time, t_philo *philo, char msg[]);
void	philo_eat(t_philo *philo);

/* ==== DEBUG.C ==== */

void	philo_id(pthread_mutex_t *write_mutex, t_philo *philo);

/* ==== INIT.C ==== */

int		init_philo(t_table *table, pthread_mutex_t *write_mut, size_t index);
int		init_philos(t_table *table, int n_philos, pthread_mutex_t *write_mut);
int		init_forks(t_table *table, int n_philo);
void	init_table(t_table *table, int n_philo, pthread_mutex_t *write_mutex);

/* ===== MAIN.C ==== */

void	*routine(void *arg);
int		join_philos(t_table *table);
int		main(int argc, char *argv[]);
#endif
