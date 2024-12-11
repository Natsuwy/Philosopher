#ifndef PHILO_H
# define PHILO_H

# define TRUE		1
# define FALSE		0
# define UNLIMITED	-1

# include "colors.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status {
	LIVING,		// when philo enjoys life with meaningful reasons
	FINISHED,	// when philo ate enough, but still living
	DIED,		// when philo dies
	END			// when monitor stops simulation
}	t_status;

typedef enum e_activity {
	FORKS,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_activity;

typedef struct 			s_philo
{
	pthread_mutex_t 	*forks_m; 		// --shared
	pthread_mutex_t 	*print_m; 		// --shared
	pthread_mutex_t 	*start_m; 		// --shared
	int					*start; 		// --shared
	int					die;      		// --local
	int 				eat;      		// --local
	int 				sleep;    		// --local
	int 				to_eat;    		// --local
	int 				index;    		// --local
	int 				philos_nb;		// --local
	long 				origin;			// --local
	long 				last_meal;		// --local

	pthread_mutex_t 	*status_m;		// --shared
	int					*status;		// --shared
}						t_philo;

typedef struct 			s_config
{
	t_philo 			*philos;        // size:av[1]
	pthread_t 			*thread;        // size:av[1]
	pthread_mutex_t 	*forks_m;		// size:av[1]
	pthread_mutex_t 	print_m;		// size:1
	pthread_mutex_t 	start_m; 		// size:1
	int					start;
	int					die;
	int					eat;
	int					sleep;
	int					to_eat;
	int					philos_nb;

	pthread_mutex_t 	*status_m;		// size:av[1]
	int					*status;		// size:av[1]
}		t_config;


/* -------- error_handler.c -------- */
void	args_nb_error(void);
void	args_value_error(void);
int		is_av_usable(int ac, char **av);


/* -------- setup.c -------- */
void	free_config(t_config *config);
int		init_config(t_config *config, char **av);
void	init_philos(t_config *config);
int		get_start(t_philo *philo);


/* -------- utils_1.c -------- */
int		ft_atoi(const char *s);
long	get_time_ms(struct timeval it);
void	print_activity(t_philo *philo, t_activity activity);


/* -------- status.c -------- */
int		is_the_end(t_philo *philo);
void	set_status(t_philo *philo, t_status status);


/* -------- forks.c -------- */
void	take_forks(t_philo *philo);
void	free_forks(t_philo *philo);


/* -------- monitor.c -------- */
void	start_simulation(t_config *config);
void	monitoring(t_config *config);
void	end_simulation(t_config *config);


/* -------- main.c -------- */
void	*routine(void *test);
void	start_simulation(t_config *config);
int		main(int ac, char **av);

#endif