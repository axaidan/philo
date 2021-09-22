#include "philosophers.h"

static void	grab_fork(t_philo *philo, t_mutex *fork_ptr)
{
	pthread_mutex_lock(fork_ptr);
	message(philo, "has taken a fork", FALSE);
	philo->forks++;
}

void	thinking(t_philo *philo)
{
	if ((philo->last_state != SLEPT && philo->last_state != BORN)
			|| philo->forks != 0)
		return ;
	philo->last_state = THOUGHT;
	if (philo->n % 2 == 0)
	{
		if (philo->right_ptr != NULL)
			grab_fork(philo, philo->right_ptr);
		if (philo->left_ptr != NULL)
			grab_fork(philo, philo->left_ptr);
	}
	else
	{
		if (philo->left_ptr != NULL)
			grab_fork(philo, philo->left_ptr);
		if (philo->right_ptr != NULL)
			grab_fork(philo, philo->right_ptr);
	}
}

void	eating(t_philo *philo)
{
	t_tstamp	timestamp;

	if (philo->last_state != THOUGHT || philo->forks != 2)
		return ;
	philo->last_state = ATE;
	timestamp = get_timestamp();
	philo->death_time = timestamp + philo->params->die;
	message(philo, "is eating", FALSE);
	safe_sleep(timestamp + philo->params->eat);
	if (philo->must_eat != -1)
		philo->must_eat--;
	if (philo->right_ptr != NULL)
	{
		pthread_mutex_unlock(philo->right_ptr);
		philo->forks--;
	}
	if (philo->left_ptr != NULL)
	{
		pthread_mutex_unlock(philo->left_ptr);
		philo->forks--;
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->last_state != ATE || philo->forks != 0)
		return ;
	philo->last_state = SLEPT;
	message(philo, "is sleeping", FALSE);
	safe_sleep(get_timestamp() + philo->params->slp);
	message(philo, "is thinking", FALSE);
}
