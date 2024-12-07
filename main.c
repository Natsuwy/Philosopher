/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:42:09 by michen            #+#    #+#             */
/*   Updated: 2024/12/07 19:04:00 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_config(t_config *config, char **av)
{
	config->philos_nb = ft_atoi(av[1]);
	config->die = ft_atoi(av[2]);
	config->eat = ft_atoi(av[3]);
	config->sleep = ft_atoi(av[4]);
	config->philos = malloc(sizeof(t_philo) * config->philos_nb);
	config->forks_m = malloc(sizeof(pthread_mutex_t *) * config->philos_nb);
	config->print_m = malloc(sizeof(pthread_mutex_t));
	config->start_m = malloc(sizeof(pthread_mutex_t));
	if (!config->philos || !config->forks_m || !config->print_m
		|| !config->start_m)
	{
		free(config->philos);
		free(config->forks_m);
		free(config->print_m);
		free(config->start_m);
		return (0);
	}
	pthread_mutex_init(config->start_m, NULL);
	pthread_mutex_init(config->print_m, NULL);
	pthread_mutex_lock(config->start_m);
	return (1);
}

void	init_philos(t_config *config)
{
	int		x;

	x = 0;
	while (x < config->philos_nb)
	{
		config->philos[x].die = config->die;
		config->philos[x].eat = config->eat;
		config->philos[x].sleep = config->sleep;
		config->philos[x].index = x;
		config->philos[x].philos_nb = config->philos_nb;
		config->philos[x].forks_m[x] = malloc(sizeof(pthread_mutex_t)); //SIGSEV
		pthread_mutex_init(config->philos[x].forks_m[x], NULL);
		x++;
	}
	return ;
}

int	main(int ac, char **av)
{
	// pthread_t		*phil;
	// pthread_mutex_t	*forks;
	t_config		config;

	if (!is_av_usable(ac, av) || !init_config(&config, av))
		return (0);
	init_philos(&config);
	// simulation....
}

// fonction check params de av
// verifie si av[1] est positif appel : is_av_usable(ac, av)
//					-> bad params nb => args_nb_error() & return false
//					-> av[1] <= 0 => args_value_error() & return false
//					-> av[2] <= 0 => args_value_error() & return false
//					-> av[3] <= 0 => args_value_error() & return false
//					-> av[4] <= 0 => args_value_error() & return false
//					-> return true

// init_config(ac, av)	=> return NULL if philos ou forks_m malloc fail
//						=> init print et start et tu lock start
//						=> atoi et assign tous les int

// init_philos(t_config *) => assign les values (tab et les ints)

// unlock start_m 'philos_nb' fois