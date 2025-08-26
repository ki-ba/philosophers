/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:49:20 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/26 14:41:22 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

/**
 * @brief converts time to eat, die, sleep, given in ms as arguments,
 * @brief to equivalent microseconds while preventing them to be greater than
 * @brief INT_MAX.
*/
static int	convert_args(t_table *table)
{
	int	max_ms;

	max_ms = INT_MAX / 1000;
	if (table->args[T_DIE] > max_ms || table->args[T_EAT] > max_ms)
		return (1);
	if (table->args[T_SLEEP] > max_ms)
		return (1);
	table->args[T_DIE] *= 1000;
	table->args[T_EAT] *= 1000;
	table->args[T_SLEEP] *= 1000;
	return (0);
}

/**
	* @brief parses argv and ensuring no arg is greater than INT_MAX.
	* @brief while it should not be a problem since the args are stored in
	* @brief an array of ssize_t, INT_MAX is already more than enough for
	* @brief reasonable use.
*/
int	parse_args(t_table *table, int argc, char **argv)
{
	size_t	i;

	i = 0;
	if (argc < 6)
		table->args[MEAL_OBJ] = 0;
	else
		table->args[MEAL_OBJ] = ft_atoi(argv[MEAL_OBJ + 1]);
	table->args[N_PHILO] = ft_atoi(argv[N_PHILO + 1]);
	table->args[T_DIE] = ft_atoi(argv[T_DIE + 1]);
	table->args[T_EAT] = ft_atoi(argv[T_EAT + 1]);
	table->args[T_SLEEP] = ft_atoi(argv[T_SLEEP + 1]);
	if (convert_args(table))
		return (error(EXIT_FAILURE));
	while (i < MEAL_OBJ + 1)
	{
		if (table->args[i] < 0)
			return (error(EXIT_FAILURE));
		++i;
	}
	return (0);
}
