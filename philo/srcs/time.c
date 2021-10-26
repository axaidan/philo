#include "philosophers.h"

int	death_occured(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->params->death_mutex);
	dead = philo->params->death;
	pthread_mutex_unlock(&philo->params->death_mutex);
	return (dead);
}

void	safe_sleep(t_tstamp until, t_philo *philo)
{
	while (get_timestamp() < until && death_occured(philo) == FALSE)
		usleep(WAIT_UNIT_US);
}

t_tstamp	get_timestamp(void)
{
	static int			first = TRUE;
	static t_timeval	zero;
	long unsigned int	timestamp;
	t_timeval			calculation;
	t_timeval			now;

	if (first == TRUE)
	{
		first = FALSE;
		gettimeofday(&zero, NULL);
	}
	gettimeofday(&now, NULL);
	calculation.tv_sec = now.tv_sec - zero.tv_sec;
	timestamp = calculation.tv_sec * 1000 + (now.tv_usec - zero.tv_usec) / 1000;
	return (timestamp);
}
