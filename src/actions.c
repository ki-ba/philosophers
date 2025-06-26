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

	time_ms = cur_ms(table->start_time, &table->tz);
	pthread_mutex_lock(&table->write);
	ft_printf("%d	", time_ms);
	ft_printf("%d ", philo->index);
	ft_printf("%s", msg);
	pthread_mutex_unlock(&table->write);
}

int	philo_eat(t_table *table, t_philo *philo)
{
	while (take_forks(table, philo))
	{
		if (should_stop(table, philo))
			return (1);
	}
	philo->last_meal = cur_ms(table->start_time, &table->tz);
	philo_log(table, philo, "is eating\n");
	increment_meals(table, philo);
	smart_usleep(table, philo, table->args[T_EAT]);
	drop_fork(philo->forks[0]);
	drop_fork(philo->forks[1]);
	return (table->weird_smell);
}

int	philo_sleep(t_table *table, t_philo *philo)
{
	philo_log(table, philo, "is sleeping\n");
	return (smart_usleep(table, philo, table->args[T_SLEEP]));
}

int	philo_think(t_table *table, t_philo *philo)
{
	philo_log(table, philo, "is thinking\n");
	return (smart_usleep(table, philo, 1));
}
