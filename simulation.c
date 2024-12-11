/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:40:39 by michen            #+#    #+#             */
/*   Updated: 2024/12/11 19:02:36 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_simulation(t_config *config)
{
	int		x;

	x = 0;
	pthread_mutex_lock(&(config->start_m));
	while (x < config->philos_nb)
	{
		pthread_create(&(config->thread[x]), NULL, &routine, &(config->philos[x]));
		x++;
	}

	config->start = TRUE;
	pthread_mutex_unlock(&(config->start_m));
}

void monitoring(t_config *config)
{
	int	x;
	int	finished_nb;
	int	status;

	while (TRUE)
	{
		x = 0;
		finished_nb = 0;
		while (x < config->philos_nb)
		{
			pthread_mutex_lock(&(config->status_m[x]));
			status = config->status[x];
			pthread_mutex_unlock(&(config->status_m[x]));
			if (status == FINISHED)
				finished_nb++;
			if (status == DIED)
				return;
			x++;
		}
		if (finished_nb == config->philos_nb)
			return;
	}
}

void end_simulation(t_config *config)
{
	int x;

	x = 0;
	while (x < config->philos_nb)
	{
		pthread_mutex_lock(&(config->status_m[x]));
		config->status[x] = END;
		pthread_mutex_unlock(&(config->status_m[x]));
		x++;
	}

	x = 0;
	while (x < config->philos_nb)
	{
		pthread_join(config->thread[x], NULL);
		x++;
	}
}
