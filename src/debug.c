/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:02:05 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/23 14:27:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	table_id(t_table *table)
{
	ssize_t	i;

	i = -1;
	pthread_mutex_lock(&table->write);
	ft_printf("\n\n\n");
	ft_printf("\nTABLE\n");
	ft_printf("%d philosophers\n", table->args[N_PHILO]);
	ft_printf("time to die : %d\n", table->args[T_DIE]);
	ft_printf("time to eat: %d\n", table->args[T_EAT]);
	ft_printf("time to sleep: %d\n", table->args[T_SLEEP]);
	ft_printf("number of meals: %d\n", table->args[MEAL_OBJ]);
	ft_printf("smell : %p (%d):\n", &table->weird_smell, table->weird_smell);
	ft_printf("forks:\n");
	while (++i < table->n_philos)
		ft_printf("%p\n", &table->forks[i]);
	i = -1;
	ft_printf("\n\nphilosophers:\n");
	while (++i < table->n_philos)
		ft_printf("%p\n", &table->philos[i]);
	ft_printf("\n\n\n");
	pthread_mutex_unlock(&table->write);
}
void	philo_id(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->write);
	ft_printf("\n\n\n");
	ft_printf("philo n. %d\n", philo->index);
	ft_printf("dead: %p\n", philo->dead);
	ft_printf("forks : %p, %p\n", philo->forks[0], philo->forks[1]);
	ft_printf("\n\n\n");
	pthread_mutex_unlock(&table->write);
}
