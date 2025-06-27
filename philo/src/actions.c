/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:59:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/23 16:24:28 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_log(t_table *table, t_philo *philo, char msg[])
{
	int	time_ms;

	if (check_death(table, philo))
		return ;
	pthread_mutex_lock(&table->write);
	time_ms = cur_ms(table->start_time, &table->tz);
	if (silent_check_death(table))
	{
		pthread_mutex_unlock(&table->write);
		return ;
	}
	printf("%d	%zu %s", time_ms, philo->index, msg);
	pthread_mutex_unlock(&table->write);
}

int	philo_die(t_table *table, t_philo *philo)
{
	int	time_ms;

	pthread_mutex_lock(&table->write);
	time_ms = cur_ms(table->start_time, &table->tz);
	printf("%d	%zu %s", time_ms, philo->index, "died\n");
	pthread_mutex_unlock(&table->write);
	return (0);
}

int	philo_eat(t_table *table, t_philo *philo)
{
	if (take_forks(table, philo))
		return (1);
	philo_log(table, philo, "is eating\n");
	increment_meals(table, philo);
	philo->last_meal = cur_ms(table->start_time, &table->tz);
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
