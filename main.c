/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:42:09 by michen            #+#    #+#             */
/*   Updated: 2024/12/12 19:26:02 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	setup_routine(t_philo *philo)
{
	struct timeval	origin;

	while (get_start(philo) == FALSE)
		continue ;
	gettimeofday(&origin, NULL);
	philo->origin = get_time_ms(origin);
	philo->last_meal = get_time_ms(origin);
	if (philo->index % 2 == 1 && fragmented_sleep(philo, philo->eat))
		return (1);
	return (0);
}

static void	count_meal(t_philo *philo)
{
	if (philo->to_eat != UNLIMITED && philo->to_eat > 0)
	{
		philo->to_eat--;
		if (philo->to_eat == 0)
			set_status(philo, FINISHED);
	}
}

void	*routine(void *info)
{
	t_philo *const	philo = info;

	if (setup_routine(philo))
		return (NULL);
	while (!is_the_end(philo))
	{
		take_forks(philo);
		print_activity(philo, EAT);
		reset_last_meal(philo);
		if (fragmented_sleep(philo, philo->eat))
		{
			free_forks(philo);
			return (NULL);
		}
		free_forks(philo);
		count_meal(philo);
		print_activity(philo, SLEEP);
		if (fragmented_sleep(philo, philo->sleep))
			return (NULL);
		print_activity(philo, THINK);
		if (philo->philos_nb % 2 == 1
			&& fragmented_sleep(philo, philo->eat - philo->sleep + 1))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_config	config;

	if (!is_av_usable(ac, av) || !init_config(&config, av))
		return (0);
	init_philos(&config);
	start_simulation(&config);
	monitoring(&config);
	end_simulation(&config);
	free_config(&config);
	return (0);
}
