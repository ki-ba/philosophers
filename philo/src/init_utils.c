/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:28:09 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/23 16:26:39 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_forks(t_fork *forks, int i)
{
	while (--i > 0)
	{
		pthread_mutex_destroy(&forks[i].fork_mutex);
	}
	free(forks);
	return (0);
}
