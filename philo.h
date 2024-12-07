#ifndef PHILO_H
# define PHILO_H

# include "colors.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct 			s_philo
{
	pthread_mutex_t 	**forks_m; 		// --shared
	pthread_mutex_t 	*print_m; 		// --shared
	pthread_mutex_t 	*start_m; 		// --shared
	int					die;      		// --local
	int 				eat;      		// --local
	int 				sleep;    		// --local
	int 				index;    		// --local
	int 				philos_nb;		// --local
}						t_philo;

typedef struct 			s_config
{
	t_philo 			*philos;        // size:av[1]
	pthread_mutex_t 	**forks_m;		// size:av[1]
	pthread_mutex_t 	*print_m;		// size:1
	pthread_mutex_t 	*start_m; 		// size:1
	int					die;
	int					eat;
	int					sleep;
	int					philos_nb;
}		t_config;

/* -------- error_handler.c -------- */
void	args_nb_error(void);
void	args_value_error(void);
int		is_av_usable(int ac, char **av);

/* ---------------- */
/* ---------------- */
/* ---------------- */
/* ---------------- */

int		ft_atoi(const char *s);
t_philo	*newphilosopher(int param_nb, char **param);

#endif