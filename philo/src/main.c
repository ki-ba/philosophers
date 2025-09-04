/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:05:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/26 14:42:26 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(&table->start_mut);
	pthread_mutex_unlock(&table->start_mut);
	pthread_mutex_lock(&philo->dt_mutex);
	pthread_mutex_unlock(&philo->dt_mutex);
	philo_log(table, philo->index, "is thinking");
	if (!(philo->index % 2))
		smart_usleep(table, table->args[T_EAT] / 2);
	while (!check_death(table))
	{
		if (philo_eat(table, philo))
			break ;
		if (philo_sleep(table, philo))
			break ;
		philo_think(table, philo);
	}
	return (NULL);
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
	i = -1;
	while (++i < table->n_philos)
		pthread_mutex_destroy(&(philos[i].dt_mutex));
	free(table->forks);
	free(table->philos);
	return (end_destroy_mutexes(table));
}

int	main(int argc, char *argv[])
{
	t_table			table;
	pthread_mutex_t	write_mut;
	ssize_t			i;
	t_philo			*philos;
	int				t_die;

	if (pthread_mutex_init(&write_mut, NULL))
		return (1);
	if (argc < 5 || argc > 6)
		return (error(USAGE_EXIT_CODE));
	if (init_table(&table, argc, argv, &write_mut))
		return (1);
	i = -1;
	t_die = table.args[T_DIE];
	philos = table.philos;
	gettimeofday(&table.start_time, NULL);
	while (++i < table.args[N_PHILO])
		calculate_delta(table.start_time, &philos[i].death_time, t_die);
	pthread_mutex_unlock(&table.start_mut);
	monitor(&table);
	return (join_philos(&table));
}
