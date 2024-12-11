/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:42:09 by michen            #+#    #+#             */
/*   Updated: 2024/12/11 19:58:04 by michen           ###   ########.fr       */
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

	while (!is_the_end(philo))
	{
		take_forks(philo);

		print_activity(philo, EAT);
		usleep(philo->eat * 1000);
		free_forks(philo);

		if (philo->to_eat != UNLIMITED && philo->to_eat > 0)
		{
			philo->to_eat--;
			if (philo->to_eat == 0)
				set_status(philo, FINISHED);
		}

		if (is_the_end(philo))
			return (NULL);

		print_activity(philo, SLEEP);
		usleep(philo->sleep * 1000);

		if (is_the_end(philo))
			return (NULL);

		print_activity(philo, THINK);
		if (philo->philos_nb % 2 == 1)
		{
			usleep((philo->eat - philo->sleep) * 1000);
			usleep(1000);
		}
		
		if (is_the_end(philo))
			return (NULL);
	}

	return (NULL);
}

int	main(int ac, char **av)
{
	t_config		config;
	// pthread_t		philo;

	if (!is_av_usable(ac, av) || !init_config(&config, av))
		return (0);

	init_philos(&config);
	
	start_simulation(&config);
	monitoring(&config);
	end_simulation(&config);

	free_config(&config);
	return (0);
}

//1: fragmenter usleep
//2: implementer death