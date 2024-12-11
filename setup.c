/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:55:48 by michen            #+#    #+#             */
/*   Updated: 2024/12/10 20:29:41 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_config(t_config *config)
{
	free(config->philos);
	free(config->thread);
	free(config->forks_m);
}

int	init_config(t_config *config, char **av)
{
	config->philos_nb = ft_atoi(av[1]);
	config->die = ft_atoi(av[2]);
	config->eat = ft_atoi(av[3]);
	config->sleep = ft_atoi(av[4]);
	if (av[5])
		config->to_eat = ft_atoi(av[5]);
	else
		config->to_eat = UNLIMITED;
	config->start = FALSE;
	config->philos = malloc(sizeof(t_philo) * config->philos_nb);
	config->thread = malloc(sizeof(pthread_t) * config->philos_nb);
	config->forks_m = malloc(sizeof(pthread_mutex_t) * config->philos_nb);
	if (!config->philos || !config->forks_m || !config->thread)
	{
		free_config(config);
		return (0);
	}
	pthread_mutex_init(&(config->start_m), NULL);
	pthread_mutex_init(&(config->print_m), NULL);
	return (1);
}

void	init_philos(t_config *config)
{
	int	x;

	x = 0;
	while (x < config->philos_nb)
	{
		config->philos[x].die = config->die;
		config->philos[x].eat = config->eat;
		config->philos[x].sleep = config->sleep;
		config->philos[x].to_eat = config->to_eat;
		config->philos[x].index = x;
		config->philos[x].start = &config->start;
		config->philos[x].philos_nb = config->philos_nb;
		config->philos[x].print_m = &config->print_m;
		config->philos[x].start_m = &config->start_m;
		config->philos[x].forks_m = config->forks_m;
		pthread_mutex_init(&(config->philos[x].forks_m[x]), NULL);
		x++;
	}
}

int	get_start(t_philo *philo)
{
	int	start;

	pthread_mutex_lock(philo->start_m);
	start = *philo->start;
	pthread_mutex_unlock(philo->start_m);
	return (start);
}