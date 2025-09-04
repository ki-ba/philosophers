/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:32:33 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/04 23:09:29 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	error(int errcode)
{
	if (errcode == ERR_USAGE)
		ft_putstr_fd("usage : ./philo t_die t_eat t_sleep [n_meals]\n", 2);
	else if (errcode == ERR_OVERFLOW)
		ft_putstr_fd("error : one of the args is too big\n", 2);
	else if (errcode == ERR_NEGATIVE || errcode == ERR_NON_NUMERIC)
		ft_putstr_fd("error : one of the args is negative / non numeric\n", 2);
	else if (errcode == ERR_NULL)
		ft_putstr_fd("error : n_philo and n_meals can't be zero\n", 2);
	else if (errcode == ERR_INIT)
		ft_putstr_fd("error : failed to init data\n", 2);
	else if (errcode == ERR_MEMORY)
		ft_putstr_fd("error : failed to allocate memory\n", 2);
	return (errcode);
}
