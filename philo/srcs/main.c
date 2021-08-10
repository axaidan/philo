#include "philosophers.h"

/*  GLOBALS */

static void	init_philo(t_philo *philo, int n, pthread_mutex_t *mutexes, t_params *args)
{
	philo->thread = 0;
	philo->first_cycle = TRUE;
	philo->n = n;
	philo->forks = 0;
	philo->state = WAITING;
	philo->mutexes = mutexes;
	philo->args = args;
}

long unsigned int	get_timestamp(/*t_timeval now, t_timeval zero*/void)
{
	static int          first = TRUE;
	static t_timeval    zero;
	long unsigned int	timestamp;
	t_timeval			calculation;
	t_timeval			now;

	if (first == TRUE)
		gettimeofday(&zero, NULL);
	gettimeofday(&now, NULL);
	calculation.tv_sec = now.tv_sec - zero.tv_sec;
	calculation.tv_usec = calculation.tv_sec * 1000000 + now.tv_usec - zero.tv_usec;
	timestamp = calculation.tv_usec / 1000;
	return (timestamp);
}

void	*routine(void *param)
{
	t_philo				*philo;
	int	i = 0;

	philo = param;
	if (philo->n % 2 == 1)
		think(philo);
	else
		usleep(WAIT_UNIT_US);
	while (g_dead == 0)
	{
		think(philo);
		eat(philo);
		printf("%d\n", i++);
	/*
		drop_forks(philo);
		sleep(philo);
	*/
	}
	return (NULL);
}

static void	two_philos(t_params *args)
{
	t_philo			philo1;
	t_philo			philo2;
	pthread_mutex_t	mutexes[2];

	pthread_mutex_init(&mutexes[0], NULL);
	pthread_mutex_init(&mutexes[1], NULL);
	init_philo(&philo1, 1, mutexes, args);
	init_philo(&philo2, 2, mutexes, args);
	pthread_create(&philo1.thread, NULL, &routine, &philo1);
//	pthread_detach(philo1.thread);
	pthread_create(&philo2.thread, NULL, &routine, &philo2);
//	pthread_detach(philo2.thread);
	pthread_join(philo1.thread, NULL);
	pthread_join(philo2.thread, NULL);
	pthread_mutex_destroy(mutexes);
	pthread_mutex_destroy(mutexes + 1);
}

int	main(int argc, char *argv[])
{
	int			error;
	t_params	params;

	g_dead = 0;
	fork1 = 0;
	fork2 = 0;
	init_params(&params);
	error = parsing(argc, argv, &params);
	if (error)
		return (error);
	display_params(&params);
	two_philos(&params);
	return (100);
}
