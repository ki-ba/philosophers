/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:07:04 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/23 16:23:44 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	time_to_ms(t_timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

int	time_to_us(t_timeval *time)
{
	return (time->tv_sec * 1000000 + time->tv_usec);
}

int	cur_ms(t_timeval start_time, t_timezone *tz)
{
	t_timeval	ttime;

	gettimeofday(&ttime, tz);
	return (time_to_ms(&ttime) - time_to_ms(&start_time));
}

int	smart_usleep(t_table *table, t_philo *philo, int time_ms)
{
	int			sleep_time;
	t_timeval	time;
	int			initial_us;

	sleep_time = 0;
	gettimeofday(&time, &table->tz);
	initial_us = time.tv_sec * 1000000 + time.tv_usec;
	while (!check_death(table, philo) && sleep_time < time_ms * 1000)
	{
		gettimeofday(&time, &table->tz);
		sleep_time = time_to_us(&time) - initial_us;
		usleep(USLEEP_STEP);
	}
	return (should_stop(table, philo));
}

int	increment_meals(t_table *table, t_philo *philo)
{
	if (++(philo->n_meals) == table->args[MEAL_OBJ])
	{
		pthread_mutex_lock(&table->meal_count_mutex);
		++(table->n_fed_philos);
		pthread_mutex_unlock(&table->meal_count_mutex);
	}
	return (0);
}
