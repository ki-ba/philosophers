/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:32:33 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/26 14:42:49 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	error(int errcode)
{
	if (errcode == USAGE_EXIT_CODE)
		ft_putstr_fd("usage : ./philo t_die t_eat t_sleep [n_meals]\n", 2);
	else if (errcode == EXIT_FAILURE)
		ft_putstr_fd("error : one of the args is incorrect\n", 2);
	return (errcode);
}
