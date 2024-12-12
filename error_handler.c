/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:40:17 by michen            #+#    #+#             */
/*   Updated: 2024/12/12 19:15:18 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	args_nb_error(void)
{
	printf(RED "Invalid number of args\n" RESET);
	printf(GREEN "Usage : ./philo <number_of_philosopher> ");
	printf("<time_to_die(ms)> <time_to_eat(ms)> <time_to_sleep(ms)>\n" RESET);
	printf(YELW "Optional : <number_of_times_");
	printf("each_philosopher_must_eat(ms)>\n" RESET);
}

void	args_value_error(void)
{
	printf(RED "Invalid number : negative/null parameter forbbiden\n" RESET);
}

void	single_philo_error(void)
{
	printf(RED "Invalid number : a philo needs a friend to eat\n" RESET);
}

int	is_av_usable(int ac, char **av)
{
	int	x;

	if (ac != 5 && ac != 6)
	{
		args_nb_error();
		return (0);
	}
	if (ft_atoi(av[1]) == 1)
	{
		single_philo_error();
		return (0);
	}
	x = 1;
	while (av[x])
	{
		if (ft_atoi(av[x]) <= 0)
		{
			args_value_error();
			return (0);
		}
		x++;
	}
	return (1);
}
