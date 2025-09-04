/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:02:19 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/05 01:32:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	init_philo(t_table *table, size_t index)
{
	t_philo		*philo;
	size_t		n_rfork;
	size_t		n_lfork;

	philo = &(table->philos[index - 1]);
	philo->dead = &(table->weird_smell);
	philo->index = index;
	philo->table = table;
	philo->dt_canary = 0;
	philo->thread_canary = 0;
	philo->n_meals = 0;
	if (pthread_mutex_init(&philo->dt_mutex, NULL))
		return (ERR_INIT);
	philo->dt_canary = 1;
	if (index == 1)
		n_lfork = table->args[N_PHILO] - 1;
	else
		n_lfork = (index - 2) % table->args[N_PHILO];
	n_rfork = index - 1;
	philo->forks[0] = &table->forks[n_lfork];
	philo->forks[1] = &table->forks[n_rfork];
	if (pthread_create(&philo->philo_thread, NULL, routine, philo))
		return (ERR_INIT);
	philo->thread_canary = 1;
	return (0);
}

int	init_philos(t_table *table, ssize_t n_philos)
{
	ssize_t	i;

	i = 0;
	table->n_philos = 0;
	while (i < n_philos)
	{
		if (init_philo(table, i + 1))
			break ;
		++i;
		table->n_philos = i;
	}
	if (table->n_philos != n_philos)
		return (ERR_INIT);
	return (0);
}

int	init_forks(t_table *table, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (pthread_mutex_init(&(table->forks[i].fork_mutex), NULL))
		{
			destroy_forks(table->forks, i);
			table->forks = NULL;
			return (ERR_INIT);
		}
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	if (!pthread_mutex_init(&table->write, NULL))
	{
		if (!pthread_mutex_init(&table->start_mut, NULL))
		{
			if (!pthread_mutex_init(&table->meal_count_mutex, NULL))
			{
				if (!pthread_mutex_init(&table->death, NULL))
					return (0);
				pthread_mutex_destroy(&table->meal_count_mutex);
			}
			pthread_mutex_destroy(&table->start_mut);
		}
		pthread_mutex_destroy(&table->write);
	}
	ft_putstr_fd("failed to init mutex\n", 2);
	return (1);
}

int	init_table(t_table *table)
{
	int	err;

	if (init_mutexes(table))
		return (ERR_INIT);
	table->weird_smell = 0;
	table->n_fed_philos = table->args[N_PHILO] * (table->args[MEAL_OBJ] == 0);
	table->philos = ft_calloc(table->args[N_PHILO], sizeof(t_philo));
	table->forks = ft_calloc(table->args[N_PHILO], sizeof(t_fork));
	if (!table->forks || !table->philos)
	{
		table->n_philos = 0;
		destroy_table(table);
		return (ERR_MEMORY);
	}
	err = init_forks(table, table->args[N_PHILO]);
	pthread_mutex_lock(&table->start_mut);
	if (!err)
		err = init_philos(table, table->args[N_PHILO]);
	if (err)
	{
		pthread_mutex_unlock(&table->start_mut);
		(destroy_table(table));
		return (err);
	}
	return (0);
}
