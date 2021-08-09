#include "philosophers.h"

void	grab_fork1(t_philo *philo)
{
	t_timeval			now;
	long unsigned int	timestamp;

	pthread_mutex_lock(philo->mutexes);
	fork1 = TRUE;
	pthread_mutex_unlock(philo->mutexes);
	philo->forks++;
	gettimeofday(&now, NULL);
	timestamp = get_timestamp(now, philo->zero);
	printf("%15lu philo %d grabbed a fork\n", timestamp, philo->n);
}

void	grab_fork2(t_philo *philo)
{
	t_timeval			now;
	long unsigned int	timestamp;

	pthread_mutex_lock(philo->mutexes + 1);
	fork2 = TRUE;
	pthread_mutex_unlock(philo->mutexes + 1);
	philo->forks++;
	gettimeofday(&now, NULL);
	timestamp = get_timestamp(now, philo->zero);
	printf("%15lu philo %d grabbed a fork\n", timestamp, philo->n);
}

void	grab_forks(t_philo *philo)
{
	while (philo->forks < 2)
	{
		if (fork1 == FALSE && philo->forks < 2)
			grab_fork1(philo);
		if (fork2 == FALSE && philo->forks < 2)
			grab_fork2(philo);
	}
}
