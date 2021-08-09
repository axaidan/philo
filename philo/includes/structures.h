#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct timeval	t_timeval;

typedef struct	s_philo
{
	pthread_t	thread;
	int			first_cycle;
	int			n;
	int			forks;
	int			state;
	t_timeval	death_time;
	t_timeval	sleep_time;
	t_timeval	think_time;
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
