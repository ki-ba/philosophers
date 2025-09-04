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
	philo_log(table, philo->index, THINK_MSG);
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
		if (philos[i].thread_canary)
			pthread_join((philos[i].philo_thread), NULL);
	}
	i = -1;
	while (++i < table->n_philos)
	{
		if (philos[i].dt_canary)
			pthread_mutex_destroy(&(philos[i].dt_mutex));
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table			table;
	ssize_t			i;
	t_philo			*philos;
	int				t_die;
	int				err;

	err = parse_args(&table, argc, argv);
	if (err)
		return (error(err));
	err = (init_table(&table));
	if (err)
		return (error(err));
	i = -1;
	t_die = table.args[T_DIE];
	philos = table.philos;
	gettimeofday(&table.start_time, NULL);
	while (++i < table.args[N_PHILO])
		calculate_delta(table.start_time, &philos[i].death_time, t_die);
	pthread_mutex_unlock(&table.start_mut);
	monitor(&table);
	return (destroy_table(&table));
}
