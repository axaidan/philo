#include "philosophers.h"

int	dead = FALSE;

int	fork1 = 0;
int	fork2 = 0;

static void	init_philo(t_philo *philo, int n)
{
	philo->first_cycle = TRUE;
	philo->thread = 0;
	philo->n = n;
	philo->forks = 0;
	philo->state = -1;
}

void	*routine(t_philo *philo)

static void	two_philos(void)
{
	t_philo		philo1;
	t_philo		philo2;
	t_timeval	zero;

	gettimeofday(&zero, NULL); 
	init_philo(&philo1, 1/*, zero*/);
	init_philo(&philo2, 2/*, zero*/);
	pthread_create(&philo1.thread, NULL, &routine, &philo1);
	pthread_create(&philo2.thread, NULL, &routine, &philo2);
	pthread_detach(philo1.thread);
	pthread_detach(philo2.thread);
	pthread_join(philo1.thread, NULL);
	pthread_join(philo2.thread, NULL);
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
