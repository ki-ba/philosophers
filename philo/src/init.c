/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:02:19 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 17:08:11 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_table *table, size_t index)
{
	t_philo		*philo;
	size_t		n_rfork;
	size_t		n_lfork;

	philo = &(table->philos[index - 1]);
	philo->dead = &(table->weird_smell);
	philo->index = index;
	philo->table = table;
	philo->n_meals = 0;
	if (pthread_mutex_init(&philo->dt_mutex, NULL))
	{
		ft_putstr_fd("failed to init mutex\n", 2);
		return (1);
	}
	if (index == 1)
		n_lfork = table->n_philos - 1;
	else
		n_lfork = (index - 2) % table->n_philos;
	n_rfork = index - 1;
	philo->forks[0] = &table->forks[n_lfork];
	philo->forks[1] = &table->forks[n_rfork];
	if (pthread_create(&philo->philo_thread, NULL, routine, philo))
		return (1);
	return (0);
}

int	init_philos(t_table *table, size_t n_philos)
{
	size_t	i;

	i = 0;
	while (i < n_philos)
	{
		if (init_philo(table, i + 1))
		{
			table->n_philos = i;
			ft_putstr_fd("warning : >= 1 philos couldnt be created.\n", 2);
			break ;
		}
		++i;
	}
	return (0);
}

int	init_forks(t_table *table, int n_philo)
{
	int	i;

	i = -1;
	if (table->philos == NULL)
		return (1);
	table->forks = ft_calloc(n_philo, sizeof(t_fork));
	if (!table->forks)
	{
		ft_putstr_fd("failed to allocate memory\n", 2);
		free(table->philos);
		return (1);
	}
	while (++i < n_philo)
	{
		if (pthread_mutex_init(&(table->forks[i].fork_mutex), NULL))
		{
			ft_putstr_fd("failed to init mutex\n", 2);
			free(table->philos);
			destroy_forks(table->forks, i);
			return (1);
		}
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	if (!pthread_mutex_init(&table->start_mut, NULL))
	{
		if (!pthread_mutex_init(&table->meal_count_mutex, NULL))
		{
			if (!pthread_mutex_init(&table->death, NULL))
				return (0);
			pthread_mutex_destroy(&table->death);
			pthread_mutex_destroy(&table->meal_count_mutex);
		}
		pthread_mutex_destroy(&table->start_mut);
	}
	ft_putstr_fd("failed to init mutex\n", 2);
	return (1);
}

int	init_table(t_table *table, int ac, char *av[], pthread_mutex_t *write)
{
	if (parse_args(table, ac, av))
		return (1);
	table->weird_smell = 0;
	table->write = *write;
	if (init_mutexes(table))
		return (1);
	pthread_mutex_lock(&table->start_mut);
	table->n_fed_philos = 0;
	table->philos = ft_calloc(table->args[N_PHILO], sizeof(t_philo));
	if (init_forks(table, table->args[N_PHILO]))
		return (destroy_mutexes(table) + 1);
	table->n_philos = table->args[N_PHILO];
	if (!table->forks || !table->philos)
		return (destroy_mutexes(table) + 1);
	if (init_philos(table, table->args[N_PHILO]))
	{
		destroy_forks(table->forks, table->args[N_PHILO]);
		return (destroy_mutexes(table) + 1);
	}
	return (0);
}
