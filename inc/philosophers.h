/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/23 14:31:54 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include "ft_printf.h"

/* time to eat in ms*/
# define TIME_TO_EAT 500

/* time to die in ms */
# define TIME_TO_DIE 2000

/* time to sleep in ms */
# define TIME_TO_SLEEP 500

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef USLEEP_STEP
#  define USLEEP_STEP 1000 
# endif

# define TRUE 1
# define FALSE 0

# define N_PHILO 0
# define T_DIE 1
# define T_EAT 2
# define T_SLEEP 3
# define MEAL_OBJ 4

typedef struct timeval	t_timeval;
typedef struct timezone	t_timezone;
typedef struct s_table	t_table;

typedef struct s_fork
{
	int				in_use;
	pthread_mutex_t	fork_mutex;
}					t_fork;

typedef struct s_philo
{
	t_fork			*forks[2];
	int				*dead;
	size_t			index;
	ssize_t			n_meals;
	pthread_t		philo_thread;
	int				last_meal;
	t_table			*table;
}					t_philo;

typedef struct s_table
{
	t_fork			*forks;
	int				weird_smell;
	int				time_ms;
	ssize_t			n_fed_philos;
	ssize_t			n_philos;
	t_philo			*philos;
	ssize_t			args[5];
	t_timeval		start_time;
	t_timeval		time;
	t_timezone		tz;
	pthread_mutex_t	time_mut;
	pthread_mutex_t	meal_count_mutex;
	pthread_mutex_t	start;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
}					t_table;

typedef struct s_table_th
{
	t_table	*table;
	size_t	index;
}			t_table_th;

/* definitely NOT libft :) */

void	*ft_calloc(size_t nmemb, size_t size);
ssize_t	ft_atoi(const char *nptr);
int		ft_iswhitespace(int c);
int		ft_isdigit(int c);

/* ==== ACTIONS.C ==== */

void	philo_log(t_table *table, t_philo *philo, char msg[]);
int		philo_eat(t_table *table, t_philo *philo);
int		philo_sleep(t_table *table, t_philo *philo);
int		philo_think(t_table *table, t_philo *philo);

/* ==== ACTION UTILS.C ==== */

int		take_fork(t_table *table, size_t index, t_fork *fork);
int		drop_fork(t_fork *fork);
int		check_death(t_table *table, t_philo *philo);
int		should_stop(t_table *table, t_philo *philo);
int		take_forks(t_table *table, t_philo *philo);

/* ==== DEBUG.C ==== */

void	philo_id(t_table *table, t_philo *philo);
void	table_id(t_table *table);

/* ==== INIT.C ==== */

int		init_philo(t_table *table, size_t index);
int		init_philos(t_table *table, size_t n_philos);
int		init_forks(t_table *table, int n_philo);
int		init_table(t_table *table, int ac, char *av[], pthread_mutex_t *write);

/* ==== DESTROY.C ==== */

int		destroy_forks(t_fork *forks, int i);
int		destroy_mutexes(t_table *table);

/* ===== MAIN.C ==== */

void	*routine(void *arg);
int		join_philos(t_table *table);
int		main(int argc, char *argv[]);

/* ==== UTILS.C ==== */

int		time_to_ms(t_timeval *time);
int		cur_ms(t_timeval start_time, t_timeval *time, t_timezone *tz);
int		smart_usleep(t_table *table, t_philo *philo, int time_ms);
int		increment_meals(t_table *table, t_philo *philo);

/* ==== PARSING.C ==== */

int		parse_args(t_table *table, int argc, char *argv[]);

#endif
