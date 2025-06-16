/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:02:19 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/16 15:01:13 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int	init_philo(t_table *table, pthread_mutex_t *write_mut, size_t index)
{
	t_philo	*philo;
	size_t	n_rfork;
	size_t	n_lfork;

	philo = &(table->philos[index - 1]);
	philo->index = index;
	philo->write_mutex = write_mut;
	philo->philo_thread = ft_calloc(1, sizeof(pthread_t));
	philo->last_meal = ft_calloc(1, sizeof(t_timeval));
	philo->start_time = ft_calloc(1, sizeof(t_timeval));
	gettimeofday(philo->last_meal, philo->tz);
	gettimeofday(philo->start_time, philo->tz);
	philo->start_time_ms = philo->start_time->tv_sec * 1000 + philo->start_time->tv_usec / 1000;
	philo->start_mutex = table->start;
	if (index == 1)
		n_lfork = table->n_philos - 1;
	else
		n_lfork = (index - 2) % table->n_philos;
	n_rfork = index - 1;
	// pthread_mutex_lock(write_mut);
	// ft_printf("%d forks : %d ; %d\n", philo->index, n_lfork, n_rfork);
	// pthread_mutex_unlock(write_mut);
	philo->forks[0] = &table->forks[n_lfork];
	philo->forks[1] = &table->forks[n_rfork];
	if (DEBUG)
		philo_id(write_mut, philo);
	if (pthread_create(philo->philo_thread, NULL, routine, philo))
		return (1);
	return (0);
}

int	init_philos(t_table *table, int n_philos, pthread_mutex_t *write_mut)
{
	ssize_t	i;

	i = -1;
	while (++i < n_philos)
		if (init_philo(table, write_mut, i + 1))
			return (1);
	return (0);
}

int	init_forks(t_table *table, int n_philo)
{
	int	i;

	i = 0;
	table->forks = ft_calloc(n_philo, sizeof(t_fork));
	if (!table->forks)
		return (-1);
	while (i < n_philo)
	{
		table->forks[i].fork_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
		pthread_mutex_init(table->forks[i].fork_mutex, NULL);
		++i;
	}
	return (0);
}
void	init_table(t_table *table, int n_philo, pthread_mutex_t *write_mutex)
{
	table->start = ft_calloc(1, sizeof(pthread_mutex_t));
	table->tz = ft_calloc(1, sizeof(t_timezone));
	table->start_time = ft_calloc(1, sizeof(t_timeval));
	gettimeofday(table->start_time, table->tz);
	pthread_mutex_init(table->start, NULL);
	pthread_mutex_lock(table->start);
	table->forks = ft_calloc(n_philo, sizeof(t_fork));
	table->philos = ft_calloc(n_philo, sizeof(t_philo));
	table->n_philos = n_philo;
	init_forks(table, n_philo);
	init_philos(table, n_philo, write_mutex);
	pthread_mutex_unlock(table->start);
}
