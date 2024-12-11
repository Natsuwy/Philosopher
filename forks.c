/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:52:08 by michen            #+#    #+#             */
/*   Updated: 2024/12/10 17:52:43 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(&philo->forks_m[philo->index]);
		pthread_mutex_lock(&philo->forks_m[(philo->index + 1) % philo->philos_nb]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks_m[(philo->index + 1) % philo->philos_nb]);
		pthread_mutex_lock(&philo->forks_m[philo->index]);
	}
}

void	free_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks_m[philo->index]);
		pthread_mutex_unlock(&philo->forks_m[(philo->index + 1) % philo->philos_nb]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks_m[(philo->index + 1) % philo->philos_nb]);
		pthread_mutex_unlock(&philo->forks_m[philo->index]);
	}
}
