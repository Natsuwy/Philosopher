/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:42:09 by michen            #+#    #+#             */
/*   Updated: 2024/12/11 16:34:46 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *info)
{
	t_philo *const	philo = info;
	struct timeval	origin;

	while (get_start(philo) == FALSE)
		continue;
	gettimeofday(&origin, NULL);
	philo->origin = get_time_ms(origin);
	philo->last_meal = get_time_ms(origin);
	while (philo->to_eat != 0)
	{
		take_forks(philo);
		print_activity(philo, EAT);
		usleep(philo->eat * 1000);
		free_forks(philo);

		print_activity(philo, SLEEP);
		usleep(philo->sleep * 1000);

		print_activity(philo, THINK);

		if (philo->to_eat != UNLIMITED)
			philo->to_eat--;
	}

	return (NULL);
}

void	start_simulation(t_config *config)
{
	int		max_philo;
	int		x;

	max_philo = config->philos_nb;
	x = 0;
	pthread_mutex_lock(&(config->start_m));
	while (x < max_philo)
	{
		pthread_create(&(config->thread[x]), NULL, &routine, &(config->philos[x]));
		x++;
	}

	config->start = TRUE;
	pthread_mutex_unlock(&(config->start_m));

	x = 0;
	while (x < max_philo)
	{
		pthread_join(config->thread[x], NULL);
		x++;
	}
}

int	main(int ac, char **av)
{
	t_config		config;
	// pthread_t		philo;

	if (!is_av_usable(ac, av) || !init_config(&config, av))
		return (0);
	init_philos(&config);
	
	// simulation....
	start_simulation(&config);
	sleep(1);
	free_config(&config);
	return (0);
}
