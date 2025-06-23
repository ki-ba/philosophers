/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:59:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/20 13:20:42 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "philosophers.h"
#include <pthread.h>

int	take_fork(t_table *table, size_t index, t_fork *fork)
{
	t_philo		*philo;

	philo = &table->philos[index - 1];
	if (should_stop(table, philo))
		return (1);
	pthread_mutex_lock(&(fork->fork_mutex));
	if (fork->in_use == 0)
	{
		fork->in_use = 1;
		philo_log(table, philo, "has taken a fork\n");
	}
	else
	{
		if (DEBUG)
			philo_log(table, philo, "could not take fork\n");
		pthread_mutex_unlock(&(fork->fork_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(fork->fork_mutex));
	return (0);
}

int	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->fork_mutex));
	if (fork->in_use == 1)
	{
		fork->in_use = 0;
	}
	else
	{
		ft_putstr_fd("ERROR : fork not in use, yet dropped\n", 2);
		pthread_mutex_unlock(&(fork->fork_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(fork->fork_mutex));
	return (0);
}

int	check_death(t_table *table, t_philo *philo)
{
	int	cur_ms_time;

	cur_ms_time = cur_ms(table->start_time, &table->time, &table->tz);
	pthread_mutex_lock(&table->death);
	if (table->weird_smell)
	{
		pthread_mutex_unlock(&table->death);
		return (1);
	}
	else if (cur_ms_time - philo->last_meal >= table->args[T_DIE])
	{
		*(philo->dead) = 1;
		pthread_mutex_unlock(&table->death);
		philo_log(table, philo, "died\n");
		if (DEBUG)
		{
			pthread_mutex_lock(&table->write);
			ft_printf("last meal : %d\n", philo->last_meal);
			pthread_mutex_unlock(&table->write);
		}
		return (1);
	}
	else if (DEBUG)
	{
		pthread_mutex_lock(&table->write);
		ft_printf("===================\n");
		ft_printf("time : %d\n", cur_ms_time);
		ft_printf("last meal : %d\n", philo->last_meal);
		ft_printf("%d\n", time_to_ms(&table->time) - philo->last_meal);
		ft_printf("===================\n");
		pthread_mutex_unlock(&table->write);
	}
	pthread_mutex_unlock(&table->death);
	return (0);
}

int	should_stop(t_table *table, t_philo *philo)
{
	int	yummy_stop;

	yummy_stop = FALSE;
	if (table->args[MEAL_OBJ] > 0)
	{
		pthread_mutex_lock(&table->meal_count_mutex);
		if (table->args[MEAL_OBJ] != 0)
		{
			if (table->n_fed_philos == table->n_philos)
			{
				// pthread_mutex_lock(&table->write);
				// ft_printf("yummy x)\n");
				// pthread_mutex_unlock(&table->write);
				yummy_stop = TRUE;
			}
			pthread_mutex_unlock(&table->meal_count_mutex);
		}
	}
	return (yummy_stop || check_death(table, philo));
}
int	take_forks(t_table *table, t_philo *philo)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = philo->forks[0];
	right_fork = philo->forks[1];
	if (should_stop(table, philo))
		return (1);
	if (philo->index % 2)
	{
		if (take_fork(table, philo->index, left_fork))
			return (10);
		if (take_fork(table, philo->index, right_fork))
		{
			drop_fork(left_fork);
			return (10);
		}
	}
	else
	{
		if (take_fork(table, philo->index, right_fork))
			return (10);
		if (take_fork(table, philo->index, left_fork))
		{
			drop_fork(right_fork);
			return (10);
		}
	}
	return (0);
}

void	philo_log(t_table *table, t_philo *philo, char msg[])
{
	int	time_ms;

	time_ms = cur_ms(table->start_time, &table->time, &table->tz);
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
		smart_usleep(table, philo, 5);
	}
	philo->last_meal = cur_ms(table->start_time, &table->time, &table->tz);
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

int philo_think(t_table *table, t_philo *philo)
{
	philo_log(table, philo, "is thinking\n");
	return (smart_usleep(table, philo, 20));
}
