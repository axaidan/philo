#include "philosophers.h"

/*  GLOBALS */
int      dead = FALSE;
int      fork1 = FALSE;
int      fork2 = FALSE;

static void	init_philo(t_philo *philo, int n, t_timeval zero, pthread_mutex_t *mutexes)
{
	philo->thread = 0;
	philo->first_cycle = TRUE;
	philo->n = n;
	philo->forks = 0;
	philo->state = WAITING;
	philo->zero = zero;
	philo->mutexes = mutexes;
}

long unsigned int	get_timestamp(t_timeval now, t_timeval zero)
{
	long unsigned int	timestamp;
	t_timeval			calculation;	

	calculation.tv_sec = now.tv_sec - zero.tv_sec;
	calculation.tv_usec = calculation.tv_sec * 1000000 + now.tv_usec - zero.tv_usec;
	timestamp = calculation.tv_usec / 1000;
	return (timestamp);
}

void	*routine(void *param)
{
	t_philo				*philo;
	t_timeval			now;
	long unsigned int	timestamp;

	philo = param;
	gettimeofday(&now, NULL);
	timestamp = get_timestamp(now, philo->zero);
//	printf("%15lu philo %d launched\n", timestamp, philo->n);
	if (philo->n % 2 == 1)
		grab_forks(philo);
	/*
	while (dead == FALSE)
	{
		grab_forks(philo);
		eat(philo);
		drop_forks(philo);
		sleep(philo);
		think(philo);
	}
	*/
	return (NULL);
}

static void	two_philos(void)
{
	t_philo			philo1;
	t_philo			philo2;
	pthread_mutex_t	mutexes[2];
	t_timeval		zero;

	gettimeofday(&zero, NULL); 
	pthread_mutex_init(&mutexes[0], NULL);
	pthread_mutex_init(&mutexes[1], NULL);
	init_philo(&philo1, 1, zero, mutexes);
	init_philo(&philo2, 2, zero, mutexes);
	pthread_create(&philo1.thread, NULL, &routine, &philo1);
	pthread_detach(philo1.thread);
	pthread_create(&philo2.thread, NULL, &routine, &philo2);
	pthread_detach(philo2.thread);
	pthread_join(philo1.thread, NULL);
	pthread_join(philo2.thread, NULL);
	pthread_mutex_destroy(mutexes);
	pthread_mutex_destroy(mutexes + 1);
}

int	main(int argc, char *argv[])
{
	int			error;
	t_params	params;

	init_params(&params);
	error = parsing(argc, argv, &params);
	if (error)
		return (error);
	display_params(&params);
	two_philos();
	return (0);
}
