/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:49:20 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/23 14:34:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	while (i < MEAL_OBJ + 1)
	{
		if (table->args[i] < 0)
		{
			ft_putstr_fd("error : one of the args is incorrect\n", 2);
			return (1);
		}
		++i;
	}
	return (0);
}
