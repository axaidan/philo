#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct timeval		t_timeval;
typedef pthread_t			t_thread;
typedef pthread_mutex_t		t_mutex;
typedef long unsigned int	t_tstamp;

typedef struct	s_params
{
	int	n;
	int	die;
	int	eat;
	int	slp;
	int	times;
}				t_params;

enum	e_last_state
{
	BORN,
	THOUGHT,
	ATE,
	SLEPT
}	;

typedef struct	s_philo
{
	t_thread		thr;
	int				n;
	int				forks;
	t_mutex			left;	
	t_mutex			*left_ptr;
	t_mutex			*right_ptr;
	t_tstamp		last_eat;
	t_tstamp		death_time;
	int				must_eat;
	int				m_init;
	int				t_init;
	t_params		*params;
	int				last_state;
}				t_philo;

int	g_dead;

#endif
