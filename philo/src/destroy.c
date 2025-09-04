/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:28:09 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 17:07:46 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	destroy_table(t_table *table)
{
	pthread_mutex_lock(&table->death);
	table->weird_smell = 1;
	pthread_mutex_unlock(&table->death);
	join_philos(table);
	destroy_forks(table->forks, table->n_philos);
	destroy_mutexes(table);
	free(table->philos);
	return (0);
}

int	destroy_forks(t_fork *forks, int i)
{
	if (!forks)
		return (1);
	while (--i > 0)
		pthread_mutex_destroy(&forks[i].fork_mutex);
	free(forks);
	return (0);
}

int	destroy_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->death);
	pthread_mutex_destroy(&table->meal_count_mutex);
	pthread_mutex_destroy(&table->start_mut);
	pthread_mutex_destroy(&table->write);
	return (0);
}

int	end_destroy_mutexes(t_table	*table)
{
	int	retval;

	retval = 0;
	retval = pthread_mutex_destroy(&table->write);
	retval = retval || pthread_mutex_destroy(&table->start_mut);
	retval = retval || pthread_mutex_destroy(&table->death);
	retval = retval || pthread_mutex_destroy(&table->meal_count_mutex);
	return (retval);
}
