/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michen <michen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:28:06 by michen            #+#    #+#             */
/*   Updated: 2024/12/19 19:23:29 by michen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0
# define UNLIMITED -1
# define UNDEFINED -2

# define FRAGMENT_US 100

# include "colors.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	LIVING,
	FINISHED,
	DIED,
	END
}					t_status;

typedef enum e_activity
{
	FORKS,
	EAT,
	SLEEP,
	THINK,
	DIE
}					t_activity;

typedef struct s_philo
{
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	*print_m;
	pthread_mutex_t	*start_m;
	int				*start;
	int				die;
	int				eat;
	int				sleep;
	int				to_eat;
	int				index;
	int				philos_nb;
	long			origin;

	pthread_mutex_t	*last_meal_m;
	long			*last_meal;


	pthread_mutex_t	*status_m;
	int				*status;
}					t_philo;

typedef struct s_config
{
	t_philo			*philos;

	pthread_t		*thread;

	pthread_mutex_t	*forks_m;

	pthread_mutex_t	print_m;

	pthread_mutex_t	start_m;
	int				start;

	int				die;
	int				eat;
	int				sleep;

	int				to_eat;

	int				philos_nb;

	pthread_mutex_t	*last_meals_m;	// sizeof(av[1])
	long			*last_meals;	// sizeof(av[1])

	pthread_mutex_t	*status_m;
	int				*status;
}					t_config;

/* -------- error_handler.c -------- */
void				args_nb_error(void);
void				args_value_error(void);
void				single_philo_error(int time_to_die_ms);
int					is_av_usable(int ac, char **av);

/* -------- setup.c -------- */
void				free_config(t_config *config);
int					init_config(t_config *config, char **av);
void				init_philos(t_config *config);
int					get_start(t_philo *philo);

/* -------- utils_1.c -------- */
int					ft_atoi(const char *s);
long				get_time_ms(struct timeval it);
void				print_activity(t_philo *philo, t_activity activity);
int					fragmented_sleep(t_philo *philo, int task_time_us);
void				reset_last_meal(t_philo *philo);

/* -------- status.c -------- */
int					must_stop(t_philo *philo);
int					must_die(t_philo *philo);
void				set_status(t_philo *philo, t_status status);

/* -------- forks.c -------- */
void				take_forks(t_philo *philo);
void				free_forks(t_philo *philo);

/* -------- monitor.c -------- */
void				start_simulation(t_config *config);
void				monitoring(t_config *config);
void				end_simulation(t_config *config);

/* -------- main.c -------- */
void				*routine(void *test);
void				start_simulation(t_config *config);
int					main(int ac, char **av);

#endif