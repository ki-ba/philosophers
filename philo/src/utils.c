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

long	time_to_ms(t_timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

int	compare_times(t_table *table, t_timeval time, int ms)
{
	t_timeval	t2;
	t_timeval	now;

	gettimeofday(&now, &table->tz);
	t2.tv_sec = time.tv_sec;
	t2.tv_usec = time.tv_usec + ms * 1000 ;
	while (t2.tv_usec >= 1000000)
	{
		t2.tv_usec -= 1000000;
		t2.tv_sec += 1;
	}
	return ((now.tv_sec - t2.tv_sec) * 1000000 + now.tv_usec - t2.tv_usec);
}

long	cur_ms(t_timeval start_time, t_timezone *tz)
{
	t_timeval	ttime;

	gettimeofday(&ttime, tz);
	return (time_to_ms(&ttime) - time_to_ms(&start_time));
}

int	smart_usleep(t_table *table, t_philo *philo, int time_ms)
{
	t_timeval	initial_time;

	gettimeofday(&initial_time, &table->tz);
	usleep(USLEEP_STEP);
	while (compare_times(table, initial_time, time_ms) <= 0)
	{
		if (check_death(table, philo))
			return (1);
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
