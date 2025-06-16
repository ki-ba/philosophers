/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:02:05 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/16 13:03:01 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_id(pthread_mutex_t *write_mutex, t_philo *philo)
{
	pthread_mutex_lock(write_mutex);
	ft_printf("\n\n\n");
	ft_printf("philo n. %d\n", philo->index);
	ft_printf("write mutex : %p\n", philo->write_mutex);
	ft_printf("start mutex : %p\n", philo->start_mutex);
	ft_printf("forks : %p, %p\n", philo->forks[0], philo->forks[1]);
	ft_printf("\n\n\n");
	pthread_mutex_unlock(write_mutex);
}
