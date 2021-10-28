#include "philosophers.h"

static void	grab_fork(t_philo *philo, t_mutex *fork_ptr)
{
	pthread_mutex_lock(fork_ptr);
	message(philo, "has taken a fork", FALSE, FALSE);
}

void	thinking(t_philo *philo)
{
	if (philo->n % 2 == 0)	// IMPAIRS
	{
		grab_fork(philo, philo->left_ptr);
		grab_fork(philo, philo->right_ptr);
	}
	else					// PAIRS
	{
		grab_fork(philo, philo->right_ptr);
		grab_fork(philo, philo->left_ptr);
	}
}

void	eating(t_philo *philo)
{
	t_tstamp	timestamp;

	message(philo, "is eating", FALSE, FALSE);
	timestamp = get_timestamp();

	pthread_mutex_lock(philo->race_ptr);
	philo->death_time = timestamp + philo->params->die;
	pthread_mutex_unlock(philo->race_ptr);

	safe_sleep(timestamp + philo->params->eat, philo);

	pthread_mutex_lock(philo->race_ptr);
	if (philo->must_eat != -1 && philo->must_eat != 0)
		philo->must_eat--;
	pthread_mutex_unlock(philo->race_ptr);
}

void	drop_forks(t_philo *philo)
{
	if (philo->n % 2 == 0)		// IMPAIRS
	{
		pthread_mutex_unlock(philo->right_ptr);
		pthread_mutex_unlock(philo->left_ptr);
	}
	else						// PAIRS
	{
		pthread_mutex_unlock(philo->left_ptr);
		pthread_mutex_unlock(philo->right_ptr);
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->must_eat == 0)
		return ;
	message(philo, "is sleeping", FALSE, FALSE);
	safe_sleep(get_timestamp() + philo->params->slp, philo);
	message(philo, "is thinking", FALSE, FALSE);
	usleep(WAIT_UNIT_US);
}
