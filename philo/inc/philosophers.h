/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/26 14:41:00 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>

# define EAT_MSG "is eating"
# define THINK_MSG "is thinking"
# define SLEEP_MSG "is sleeping"
# define DIE_MSG "died"
# define FORK_MSG "has taken a fork"

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef USLEEP_STEP
#  define USLEEP_STEP 500
# endif

# define TRUE 1
# define FALSE 0

# define USAGE_EXIT_CODE 2

/* ==== ARGS ARRAY INDEXES ==== */

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
	int				*dead;
	t_fork			*forks[2];
	t_table			*table;
	ssize_t			index;
	ssize_t			n_meals;
	pthread_t		philo_thread;
	t_timeval		death_time;
	pthread_mutex_t	dt_mutex;
}					t_philo;

typedef struct s_table
{
	int				weird_smell;
	t_fork			*forks;
	ssize_t			n_fed_philos;
	ssize_t			n_philos;
	t_philo			*philos;
	ssize_t			args[5];
	t_timeval		start_time;
	pthread_mutex_t	meal_count_mutex;
	pthread_mutex_t	start_mut;
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
void	ft_putstr_fd(char *s, int fd);

/* ==== ACTIONS.C ==== */

int		philo_log(t_table *table, ssize_t index, char msg[]);
int		philo_eat(t_table *table, t_philo *philo);
int		philo_sleep(t_table *table, t_philo *philo);
int		philo_think(t_table *table, t_philo *philo);
int		philo_die(t_table *table, t_philo *philo);

/* ==== ACTION UTILS.C ==== */

int		take_fork(t_table *table, t_philo *philo, t_fork *fork);
int		drop_fork(t_fork *fork);
int		check_death(t_table *table);
int		should_stop(t_table *table);
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
int		end_destroy_mutexes(t_table	*table);

/* ===== ERROR.C ===== */

int		error(int errcode);

/* ===== MAIN.C ==== */

void	*routine(void *arg);
int		join_philos(t_table *table);
int		main(int argc, char *argv[]);
void	print_timeval(t_timeval time);

/* ==== UTILS.C ==== */

int		smart_usleep(t_table *table, int time_ms);
int		increment_meals(t_table *table, t_philo *philo);
long	compare_times(t_timeval time);
int		compare_times_bool(t_timeval t1);
void	calculate_delta(t_timeval t1, t_timeval *t2, long delta_us);

/* ==== PARSING.C ==== */

int		parse_args(t_table *table, int argc, char *argv[]);

/* ==== MONITOR.C ==== */

int		monitor(t_table	*table);

#endif
