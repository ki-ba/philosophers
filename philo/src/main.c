/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:05:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/01 11:29:01 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	usage(void)
{
	write(2, "usage : ./philo time_die time_eat time_sleep [n_meals]\n", 56);
	return (1);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(&table->start_mut);
	pthread_mutex_unlock(&table->start_mut);
	philo_think(table, philo);
	if (philo->index % 2)
		usleep(100);
	while (!should_stop(table, philo))
	{
		if (philo_eat(table, philo))
			return (NULL);
		if (philo_sleep(table, philo))
			return (NULL);
		if (philo_think(table, philo))
			return (NULL);
	}
	return (NULL);
}

int	silent_check_death(t_table *table)
{
	int	ret;

	pthread_mutex_lock(&table->death);
	ret = table->weird_smell;
	pthread_mutex_unlock(&table->death);
	return (ret);
}

int	join_philos(t_table *table)
{
	ssize_t	i;
	t_philo	*philos;

	philos = table->philos;
	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_join((philos[i].philo_thread), NULL))
			return (1);
	}
	free(table->forks);
	free(table->philos);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table			table;
	pthread_mutex_t	write_mut;

	if (pthread_mutex_init(&write_mut, NULL))
		return (1);
	if (argc < 5 || argc > 6)
		return (usage());
	if (init_table(&table, argc, argv, &write_mut))
		return (1);
	if (join_philos(&table))
		return (1);
	pthread_mutex_destroy(&write_mut);
	pthread_mutex_destroy(&table.start_mut);
	pthread_mutex_destroy(&table.death);
	pthread_mutex_destroy(&table.meal_count_mutex);
	return (0);
}
