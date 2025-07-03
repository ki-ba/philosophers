/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:35:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/03 18:59:57 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	someone_died(t_table *table)
{
	pthread_mutex_lock(&table->death);
	table->weird_smell = 1;
	pthread_mutex_unlock(&table->death);
}

static void	check_hungryness(t_table	*table)
{
	pthread_mutex_lock(&table->meal_count_mutex);
	if (table->n_fed_philos == table->n_philos)
		someone_died(table);
	pthread_mutex_unlock(&table->meal_count_mutex);
	usleep(10000);
}

static	int	look_for_deaths(t_table *table, ssize_t i, int *death)
{
	long		time_ms;

	pthread_mutex_lock(&table->philos[i].dt_mutex);
	if (compare_times(table->philos[i].death_time) > 0)
	{
		*death = 1;
		someone_died(table);
		pthread_mutex_unlock(&table->philos[i].dt_mutex);
		pthread_mutex_lock(&table->write);
		time_ms = compare_times(table->start_time) / 1000;
		printf("%ld	%0.3zu	died\n", time_ms, i + 1);
		pthread_mutex_unlock(&table->write);
		return (1);
	}
	else
		pthread_mutex_unlock(&table->philos[i].dt_mutex);
	pthread_mutex_lock(&table->death);
	return (0);
}

int	monitor(t_table	*table)
{
	int			death;
	ssize_t		i;
	t_timeval	now;

	usleep(table->args[T_DIE] / 2);
	death = 0;
	i = 0;
	while (!death)
	{
		gettimeofday(&now, NULL);
		if (i == table->args[N_PHILO] - 1)
			check_hungryness(table);
		look_for_deaths(table, i, &death);
		if (table->weird_smell)
		{
			pthread_mutex_unlock(&table->death);
			break ;
		}
		pthread_mutex_unlock(&table->death);
		i = (i + 1) % table->args[N_PHILO];
	}
	return (0);
}
