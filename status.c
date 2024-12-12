/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:20:04 by michen            #+#    #+#             */
/*   Updated: 2024/12/12 19:19:28 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_the_end(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->status_m);
	status = *(philo->status);
	pthread_mutex_unlock(philo->status_m);
	return (status == END);
}

int	must_die(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (get_time_ms(now) - philo->last_meal >= philo->die)
	{
		pthread_mutex_lock(philo->status_m);
		*(philo->status) = DIED;
		pthread_mutex_unlock(philo->status_m);
		return (1);
	}
	return (0);
}

void	set_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(philo->status_m);
	*(philo->status) = status;
	pthread_mutex_unlock(philo->status_m);
}
