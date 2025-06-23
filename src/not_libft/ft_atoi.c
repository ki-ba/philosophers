/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:27:11 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/16 10:46:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

ssize_t	ft_atoi(const char *nptr)
{
	ssize_t	n;

	n = 0;
	while (nptr && *nptr)
	{
		if (!ft_isdigit(*nptr))
			return (-1);
		else if (n > INT_MAX / 10 || (n == INT_MAX / 10 && *nptr >= 7))
			return (-1);
		n = (n * 10) + (*nptr - 48);
		++nptr;
	}
	return (n);
}
