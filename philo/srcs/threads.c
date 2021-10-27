#include "philosophers.h"

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	pthread_mutex_lock(philo->race_ptr);
	while (death_occured(philo) == FALSE && philo->must_eat != 0)
	{
		pthread_mutex_unlock(philo->race_ptr);
		thinking(philo);
		eating(philo);
		drop_forks(philo);
		sleeping(philo);
		pthread_mutex_lock(philo->race_ptr);
	}
	pthread_mutex_unlock(philo->race_ptr);
	if (philo->params->n == 1)
		pthread_mutex_unlock(philo->left_ptr);
	return (NULL);
}

int	start_all_threads(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&(philos + i)->thr, NULL, routine, philos + i)
			!= SUCCESS)
		{
			pthread_mutex_lock(&philos->params->death_mutex);
			philos->params->death = TRUE;
			pthread_mutex_unlock(&philos->params->death_mutex);
			return (display_ret_system_err(ER_THR_CREA, philos, n));
		}
	//if (i == 0)
	//		usleep(WAIT_UNIT_US);
		(philos + i)->t_init = TRUE;
		i++;
	}
	return (SUCCESS);
}

void	join_all_threads(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n && (philos + i)->t_init == TRUE)
	{
		if (pthread_join((philos + i)->thr, NULL) != SUCCESS)
			printf("could not join thread %d\n", i);
		i++;
	}
}
