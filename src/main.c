/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:05:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/16 16:04:26 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <sys/time.h>

int	usage(void)
{
	ft_putstr_fd("usage : ./philo <time_die> <time_eat> <time_sleep> [n_meals]\n", 2);
	return (1);
}

int	are_forks_busy(t_philo *philo)
{
	t_fork	*left_fork;
	t_fork	*right_fork;
	int		busy;

	left_fork = philo->forks[0];
	right_fork = philo->forks[1];
	pthread_mutex_lock(left_fork->fork_mutex);
	busy = (left_fork->in_use);
	pthread_mutex_unlock(left_fork->fork_mutex);
	pthread_mutex_lock(right_fork->fork_mutex);
	busy = busy && right_fork->in_use;
	pthread_mutex_unlock(right_fork->fork_mutex);
	return (busy);
}
void	*routine(void *arg)
{
	t_philo		*philo;
	t_timeval	time;

	philo = ((t_philo *)arg);
	gettimeofday(&time, philo->tz);
	// philo_log(&time, philo, "philo is waiting start\n");
	pthread_mutex_lock(philo->start_mutex);
	gettimeofday(&time, philo->tz);
	// philo_log(&time, philo, "philo started\n");
	pthread_mutex_unlock(philo->start_mutex);
	while (1)
	{
		gettimeofday(&time, philo->tz);
		philo_log(&time, philo, "is thinking\n");
		while (are_forks_busy(philo))
		{
			gettimeofday(&time, philo->tz);
			if (time.tv_sec - philo->last_meal->tv_sec >= TIME_TO_DIE)
			{
				philo_log(&time, philo, "died\n");
				pthread_mutex_lock(philo->write_mutex);
				ft_printf("%d seconds since last meal\n", time.tv_sec - philo->last_meal->tv_sec);
				pthread_mutex_unlock(philo->write_mutex);
				return (NULL);
			}
			else
				usleep(10000);
		}
		philo_eat(philo);
		gettimeofday(&time, philo->tz);
		philo_log(&time, philo, "is sleeping\n");
		usleep(TIME_TO_SLEEP);
	}
	return (NULL);
}

int	join_philos(t_table *table)
{
	size_t	i;
	t_philo	*philos;

	philos = table->philos;
	i = 0;
	while (i < table->n_philos)
	{
		if (DEBUG)
		{
			pthread_mutex_lock(table->philos[i].write_mutex);
			ft_printf("joining %d\n", i);
			pthread_mutex_unlock(table->philos[i].write_mutex);
		}
		if (pthread_join(*(philos[i].philo_thread), NULL))
			return (1);
		++i;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table			table;
	pthread_mutex_t	write_mut;

	pthread_mutex_init(&write_mut, NULL);
	if (argc < 4 || ft_atoi(argv[1]) < 1)
		return (usage());
	init_table(&table, ft_atoi(argv[1]), &write_mut);
	if (join_philos(&table))
		return (1);
	pthread_mutex_destroy(&write_mut);
	pthread_mutex_destroy(table.start);
	return (0);
}
