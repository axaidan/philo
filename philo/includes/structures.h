#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct timeval	t_timeval;

typedef struct	s_params
{
	int	n;
	int	die;
	int	eat;
	int	slp;
	int	times;
}				t_params;

typedef struct	s_philo
{
	pthread_t		thread;
	int				first_cycle;
	int				n;
	int				forks;
	int				state;
	t_timeval		sleep_end;
	t_timeval		eating_end;
	t_timeval		death_time;
	pthread_mutex_t	*mutexes;
	t_params		*args;
}				t_philo;

int	g_dead;
int	fork1;
int	fork2;

#endif
