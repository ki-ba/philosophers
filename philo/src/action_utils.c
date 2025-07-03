/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:26:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/03 17:52:49 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork(t_table *table, t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&(fork->fork_mutex));
	if (fork->in_use == 0)
	{
		fork->in_use = 1;
		pthread_mutex_unlock(&(fork->fork_mutex));
		philo_log(table, philo->index, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&(fork->fork_mutex));
		return (1);
	}
	return (0);
}

int	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->fork_mutex));
	if (fork->in_use == 1)
	{
		fork->in_use = 0;
		pthread_mutex_unlock(&(fork->fork_mutex));
	}
	else
	{
		pthread_mutex_unlock(&(fork->fork_mutex));
		return (1);
	}
	return (0);
}

int	check_death(t_table *table)
{
	pthread_mutex_lock(&table->death);
	if (table->weird_smell)
	{
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	pthread_mutex_unlock(&table->death);
	return (0);
}

int	should_stop(t_table *table)
{
	int	yummy_stop;

	yummy_stop = FALSE;
	if (table->args[MEAL_OBJ] > 0)
	{
		pthread_mutex_lock(&table->meal_count_mutex);
		if (table->n_fed_philos == table->n_philos)
			yummy_stop = TRUE;
		pthread_mutex_unlock(&table->meal_count_mutex);
	}
	return (yummy_stop || check_death(table));
}

int	take_forks(t_table *table, t_philo *philo)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = philo->forks[(philo->index % 2 != 0)];
	right_fork = philo->forks[(philo->index % 2 == 0)];
	while (take_fork(table, philo, left_fork))
		if (smart_usleep(table, 300))
			return (1);
	while (take_fork(table, philo, right_fork))
		if (smart_usleep(table, 300))
			return (1);
	return (0);
}
