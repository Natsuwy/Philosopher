/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:35:39 by michen            #+#    #+#             */
/*   Updated: 2024/12/11 16:27:11 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		i;
	int		minus;
	int		res;

	str = (char *)nptr;
	i = 0;
	minus = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (minus * res);
}

long	get_time_ms(struct timeval it)
{
	return ((it.tv_sec * 1000) + (it.tv_usec / 1000));
}

void	print_activity(t_philo *philo, t_activity activity)
{
	struct timeval	now;
	long			timestamp;

	gettimeofday(&now, NULL);
	timestamp = get_time_ms(now) - philo->origin;
	pthread_mutex_lock(philo->print_m);
	if (activity == EAT)
	{
		printf("%ld %d has taken a fork\n", timestamp, philo->index);
		printf("%ld %d has taken a fork\n", timestamp, philo->index);
		printf("%ld %d is eating\n", timestamp, philo->index);
	}
	else if (activity == SLEEP)
	{
		printf("%ld %d is sleeping\n", timestamp, philo->index);
	}
	else if (activity == THINK)
	{
		printf("%ld %d is thinking\n", timestamp, philo->index);
	}
	else if (activity == DIE)
	{
		printf("%ld %d died\n", timestamp, philo->index);
	}
	pthread_mutex_unlock(philo->print_m);
}
