/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:20:04 by michen            #+#    #+#             */
/*   Updated: 2024/12/11 19:35:52 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_the_end(t_philo *philo)
{
	// printf("is_the_end\n");
	int status;

	pthread_mutex_lock(philo->status_m);
	status = *(philo->status);
	pthread_mutex_unlock(philo->status_m);

	return (status == END);
}

void	set_status(t_philo *philo, t_status status)
{
	// printf("set_status\n");

	pthread_mutex_lock(philo->status_m);
	*(philo->status) = status;
	pthread_mutex_unlock(philo->status_m);
}
