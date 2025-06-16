/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:59:47 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/16 16:31:05 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "philosophers.h"

int	take_fork(t_philo *philo, t_fork *fork)
{
	t_timeval	time;

	gettimeofday(&time, philo->tz);
	pthread_mutex_lock(fork->fork_mutex);
	if (fork->in_use == 0)
	{
		fork->in_use = 1;
		philo_log(&time, philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_unlock(fork->fork_mutex);
		return (1);
	}
	pthread_mutex_unlock(fork->fork_mutex);
	return (0);
}

int	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->fork_mutex);
	if (fork->in_use == 1)
	{
		fork->in_use = 0;
	}
	else
	{
		pthread_mutex_unlock(fork->fork_mutex);
		return (1);
	}
	pthread_mutex_unlock(fork->fork_mutex);
	return (0);
}

int	take_forks(t_philo *philo)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = philo->forks[0];
	right_fork = philo->forks[1];
	if (philo->index == 1)
	{
		if (take_fork(philo, left_fork) == 0)
		{
			if (take_fork(philo, right_fork) != 0)
			{
				drop_fork(left_fork);
				return (1);
			}
		}
		else
		{
			return (1);
		}
	}
	else
	{
		if (take_fork(philo, right_fork) == 0)
		{
			if (take_fork(philo, left_fork) != 0)
			{
				drop_fork(right_fork);
				return (1);
			}
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

void	philo_log(t_timeval *time, t_philo *philo, char msg[])
{
	pthread_mutex_t	*mutex;
	int				timestamp_ms;

	timestamp_ms = (time->tv_usec / 1000 + time->tv_sec * 1000);
	mutex = (philo->write_mutex);
	pthread_mutex_lock(mutex);
	ft_printf("%d	", timestamp_ms - philo->start_time_ms);
	ft_printf("%d ", philo->index);
	ft_printf("%s", msg);
	pthread_mutex_unlock(mutex);
}

void	philo_eat(t_philo *philo)
{
	t_timeval	time;

	if (take_forks(philo) == 0)
	{
		gettimeofday(philo->last_meal, philo->tz);
		philo_log(philo->last_meal, philo, "is eating\n");
		usleep(TIME_TO_EAT);
		drop_fork(philo->forks[0]);
		drop_fork(philo->forks[1]);
		usleep(1000);
	}
	else
	{
		gettimeofday(&time, philo->tz);
		philo_log(&time, philo, "could not eat\n");
	}
}
