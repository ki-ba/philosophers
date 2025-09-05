/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:49:20 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/05 01:33:22 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>
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
		return (ERR_OVERFLOW);
	if (table->args[T_SLEEP] > max_ms)
		return (ERR_OVERFLOW);
	table->args[T_DIE] *= 1000;
	table->args[T_EAT] *= 1000;
	table->args[T_SLEEP] *= 1000;
	return (0);
}

/**
 * @brief checks the validity of arguments given to the program.
 * @brief checks wether any of them is negative, if they are bigger than
 * @brief INT_MAX, if some of them are bigger than 1/1000  * INT_MAX.
 */
static int	check_args(int argc, char **argv)
{
	int		i;
	ssize_t	current;

	if (argc < 5 || argc > 6)
		return (ERR_USAGE);
	i = 1;
	while (i < argc)
	{
		if (ft_is_number(argv[i]) == FALSE)
			return (ERR_NON_NUMERIC);
		current = ft_atoi(argv[i]);
		if (current > INT_MAX)
			return (ERR_OVERFLOW);
		if (current < 0)
			return (ERR_NEGATIVE);
		if (current == 0 && i == N_PHILO + 1)
			return (ERR_NULL);
		if (i >= T_DIE + 1 && i <= T_SLEEP + 1)
		{
			if (current > INT_MAX / 1000)
				return (ERR_OVERFLOW);
		}
		++i;
	}
	return (SUCCESS);
}

/**
	* @brief parses argv and ensuring no arg is greater than INT_MAX.
	* @brief while it should not be a problem since the args are stored in
	* @brief an array of ssize_t, INT_MAX is already more than enough for
	* @brief reasonable use.
*/
int	parse_args(t_table *table, int argc, char **argv)
{
	int		error;

	error = check_args(argc, argv);
	if (error)
		return (error);
	if (argc < 6)
		table->args[MEAL_OBJ] = -1;
	else
		table->args[MEAL_OBJ] = ft_atoi(argv[MEAL_OBJ + 1]);
	table->args[N_PHILO] = ft_atoi(argv[N_PHILO + 1]);
	table->args[T_DIE] = ft_atoi(argv[T_DIE + 1]);
	table->args[T_EAT] = ft_atoi(argv[T_EAT + 1]);
	table->args[T_SLEEP] = ft_atoi(argv[T_SLEEP + 1]);
	convert_args(table);
	return (0);
}
