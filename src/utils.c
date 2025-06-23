/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:07:04 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/23 14:27:36 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	time_to_ms(t_timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

int	cur_ms(t_timeval start_time, t_timeval *time, t_timezone *tz)
{
	gettimeofday(time, tz);
	return (time_to_ms(time) - time_to_ms(&start_time));
}

int	smart_usleep(t_table *table, t_philo *philo, int time_ms)
{
	int	sleep_time;

	sleep_time = 0;
	while (!check_death(table, philo) && sleep_time < time_ms)
	{
		usleep(USLEEP_STEP);
		sleep_time += 1;
	}
	return (check_death(table, philo));
}

int	increment_meals(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->meal_count_mutex);
	if (++philo->n_meals == table->args[MEAL_OBJ])
	{
		++table->n_fed_philos;
	}
	pthread_mutex_unlock(&table->meal_count_mutex);
	return (0);
}
