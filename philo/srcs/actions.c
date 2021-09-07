#include "philosophers.h"

void	think(t_philo *philo)
{
	if (philo->forks == 2)
		return ;
	/*
	printf("%15lu philo %d is thinking\n", get_timestamp(), philo->n);
	while (philo->forks < 2)
	{
		if (fork1 == FALSE && philo->forks < 2)
			grab_fork1(philo);
		if (fork2 == FALSE && philo->forks < 2)
			grab_fork2(philo);
	}
	*/
}

void	eat(t_philo *philo)
{
	long unsigned int	eat_ms_time;
	long unsigned int	wait_units;

	if (philo->forks < 2)
		return ;
	printf("%15lu philo %d is eating\n", get_timestamp(), philo->n);
	eat_ms_time = philo->args->eat;
	wait_units = eat_ms_time * 20;
	while (wait_units != 0)
	{
		usleep(50);
		wait_units--;
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->forks < 2)
		return ;
	philo->forks = 0;
}

void	sleeping(t_philo *philo)
{
	long unsigned int	sleep_ms_time;

	if (philo->forks != 0)
		return ;
	printf("%15lu philo %d is sleeping\n", get_timestamp(), philo->n);
	sleep_ms_time = philo->args->slp;	
	usleep(sleep_ms_time * 1000);
}
