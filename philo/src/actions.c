/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:59:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/01 11:18:07 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

void	philo_log(t_table *table, t_philo *philo, char msg[])
{
	long	time_ms;

	pthread_mutex_lock(&table->write);
	time_ms = compare_times(table, table->start_time) / 1000;
	if (silent_check_death(table))
	{
		pthread_mutex_unlock(&table->write);
		return ;
	}
	printf("%ld	%0.2zu %s", time_ms, philo->index, msg);
	pthread_mutex_unlock(&table->write);
}

int	philo_die(t_table *table, t_philo *philo)
{
	long	time_ms;

	pthread_mutex_lock(&table->write);
	time_ms = compare_times(table, table->start_time) / 1000;
	printf("%ld	%0.2zu %s", time_ms, philo->index, "died\n");
	pthread_mutex_unlock(&table->write);
	return (0);
}

int	philo_eat(t_table *table, t_philo *philo)
{
	t_timeval	now;

	if (take_forks(table, philo))
		return (1);
	philo_log(table, philo, "is eating\n");
	increment_meals(table, philo);
	gettimeofday(&now, &table->tz);
	calculate_delta(now, &philo->death_time, table->args[T_DIE]);
	smart_usleep(table, philo, table->args[T_EAT]);
	drop_fork(philo->forks[0]);
	drop_fork(philo->forks[1]);
	return (check_death(table, philo));
}

int	philo_sleep(t_table *table, t_philo *philo)
{
	philo_log(table, philo, "is sleeping\n");
	return (smart_usleep(table, philo, table->args[T_SLEEP]));
}

int	philo_think(t_table *table, t_philo *philo)
{
	philo_log(table, philo, "is thinking\n");
	return (0);
}
