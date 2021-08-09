#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct timeval	t_timeval;

typedef struct	s_philo
{
	pthread_t		thread;
	int				first_cycle;
	int				n;
	int				forks;
	int				state;
	t_timeval		zero;
	t_timeval		sleep_end;
	t_timeval		eating_end;
	t_timeval		death_time;
	pthread_mutex_t	*mutexes;
}				t_philo;

typedef struct	s_params
{
	int	n;
	int	die;
	int	eat;
	int	slp;
	int	times;
}				t_params;

#endif
