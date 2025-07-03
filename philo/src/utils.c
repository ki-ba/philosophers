/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:07:04 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/03 18:52:37 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	compare_times(t_timeval time)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - time.tv_sec) * 1000000 + now.tv_usec - time.tv_usec);
}

void	calculate_delta(t_timeval t1, t_timeval *t2, long delta_us)
{
	t2->tv_sec = t1.tv_sec;
	t2->tv_usec = t1.tv_usec + delta_us;
	while (t2->tv_usec > 1000000)
	{
		++(t2->tv_sec);
		t2->tv_usec -= 1000000;
	}
}

/*
	* @brief compares `time` + `delta_us` with now.
	* @returns 1 if now is more than `delta_us` us later than `time`.
	* @returns 0 if `time` < `now` < `now` + `delta_us`
*/
int	compare_times_bool(t_timeval t1)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	if (now.tv_sec > t1.tv_sec)
		return (1);
	else if (now.tv_sec == t1.tv_sec && now.tv_usec >= t1.tv_usec)
		return (1);
	return (0);
}

int	smart_usleep(t_table *table, int time_us)
{
	t_timeval	initial_time;
	t_timeval	t2;

	gettimeofday(&initial_time, NULL);
	calculate_delta(initial_time, &t2, time_us);
	while (!compare_times_bool(t2))
	{
		if (check_death(table))
			return (1);
		usleep(USLEEP_STEP);
	}
	return (check_death(table));
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
