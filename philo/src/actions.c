/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:59:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/03 18:58:57 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

int	philo_log(t_table *table, ssize_t index, char msg[])
{
	long		time_ms;
	t_timeval	now;

	pthread_mutex_lock(&table->write);
	gettimeofday(&now, NULL);
	if (!check_death(table))
	{
		time_ms = compare_times(table->start_time) / 1000;
		if (DEBUG)
			printf("%ld	%ld	%0.3zu %s\n", now.tv_sec, now.tv_usec, index, msg);
		else
			printf("%ld	%0.3zu %s\n", time_ms, index, msg);
		pthread_mutex_unlock(&table->write);
		return (0);
	}
	else
		pthread_mutex_unlock(&table->write);
	return (1);
}

int	philo_eat(t_table *table, t_philo *philo)
{
	t_timeval	now;

	if (take_forks(table, philo))
		return (1);
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->dt_mutex);
	calculate_delta(now, &philo->death_time, table->args[T_DIE]);
	pthread_mutex_unlock(&philo->dt_mutex);
	if (philo_log(table, philo->index, "is eating"))
		return (1);
	if (smart_usleep(table, table->args[T_EAT]))
		return (1);
	drop_fork(philo->forks[0]);
	drop_fork(philo->forks[1]);
	increment_meals(table, philo);
	return (0);
}

int	philo_sleep(t_table *table, t_philo *philo)
{
	philo_log(table, philo->index, "is sleeping");
	return (smart_usleep(table, table->args[T_SLEEP]));
}

int	philo_think(t_table *table, t_philo *philo)
{
	philo_log(table, philo->index, "is thinking");
	if (table->args[N_PHILO] % 2 != 0 && philo->n_meals)
		return (smart_usleep(table, table->args[T_EAT]));
	return (0);
}
