/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:42:09 by michen            #+#    #+#             */
/*   Updated: 2024/12/04 12:25:27 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colors.h"

int	errinput(void)
{
	printf(RED"Invalid number of args\n"RESET);
	printf(GREEN"Usage : ./philosopher <number_of_philosopher> ");
	printf("<time_to_die(ms)> <time_to_eat(ms)> <time_to_sleep(ms)>\n"RESET);
	printf(YELW"Optional : <number_of_times_each_philosopher_must_eat(ms)>\n"RESET);
    return (1);
}

int	main(int ac, char **av)
{
	if (ac == 5)
		printf("coucou lets go\n");
    else if (ac == 6)
        printf("coucou lets go\n");
	else
		return (errinput());
    (void)av;
	return (0);
}
