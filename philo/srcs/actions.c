#include "philosophers.h"

void	grab_fork1(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes);
	fork1 = TRUE;
	pthread_mutex_unlock(philo->mutexes);
	philo->forks++;
	printf("%15lu philo %d grabbed fork 1\n", get_timestamp(), philo->n);
}

void	grab_fork2(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes + 1);
	fork2 = TRUE;
	pthread_mutex_unlock(philo->mutexes + 1);
	philo->forks++;
	printf("%15lu philo %d grabbed fork 2\n", get_timestamp(), philo->n);
}

/*
void	die(pthread_mutex_t mutex)
{


}
*/

void	think(t_philo *philo)
{
	if (philo->forks == 2)
		return ;
	printf("%15lu philo %d is thinking\n", get_timestamp(), philo->n);
	while (philo->forks < 2)
	{
		if (fork1 == FALSE && philo->forks < 2)
			grab_fork1(philo);
		if (fork2 == FALSE && philo->forks < 2)
			grab_fork2(philo);
	}
}

void	eat(t_philo *philo)
{
	long unsigned int	eat_ms_time;
	long unsigned int	wait_units;

	if (philo->forks < 2)
		return ;
	printf("%15lu philo %d is eating\n", get_timestamp(), philo->n);
	eat_ms_time = philo->args->eat;
//	printf("eat_ms_time = %lu ms\n", eat_ms_time);
	wait_units = eat_ms_time * 1000 / WAIT_UNIT_US;
	while (wait_units != 0)
	{
		printf("wait_units = %lu\n", wait_units);
		usleep(WAIT_UNIT_US);
		wait_units--;
	}
}
