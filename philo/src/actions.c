/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:59:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/01 19:28:47 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_log(t_table *table, ssize_t index, char msg[])
{
	long	time_ms;

	pthread_mutex_lock(&table->write);
	if (silent_check_death(table))
	{
		pthread_mutex_unlock(&table->write);
		return ;
	}
	time_ms = compare_times(table->start_time) / 1000;
	printf("%ld	%0.2zu %s\n", time_ms, index, msg);
	pthread_mutex_unlock(&table->write);
}

int	philo_die(t_table *table, t_philo *philo)
{
	long	time_ms;

	pthread_mutex_lock(&table->write);
	time_ms = compare_times(table->start_time) / 1000;
	printf("%ld	%0.2zu %s\n", time_ms, philo->index, "died");
	pthread_mutex_unlock(&table->write);
	return (0);
}

int	philo_eat(t_table *table, t_philo *philo)
{
	t_timeval	now;

	if (take_forks(table, philo))
		return (1);
	philo_log(table, philo->index, "is eating");
	increment_meals(table, philo);
	gettimeofday(&now, NULL);
	calculate_delta(now, &philo->death_time, table->args[T_DIE]);
	smart_usleep(table, philo, table->args[T_EAT]);
	drop_fork(philo->forks[0]);
	drop_fork(philo->forks[1]);
	return (0);
}

int	philo_sleep(t_table *table, t_philo *philo)
{
	philo_log(table, philo->index, "is sleeping");
	return (smart_usleep(table, philo, table->args[T_SLEEP]));
}

int	philo_think(t_table *table, t_philo *philo)
{
	philo_log(table, philo->index, "is thinking");
	return (0);
}
