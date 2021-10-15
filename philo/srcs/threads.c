#include "philosophers.h"

void    *routine(void *param)
{
	t_philo	*philo;
//	int		finished;

	philo = param;
//	if (philo->n % 2 == 0)
//		thinking(philo);
//	else
//		usleep(WAIT_UNIT_US);
	// LOCK philo->d_race
	// CHECK g_dead BEFORE LOOP
	// UNLOCK philo->d_race
	
	/*
	pthread_mutex_lock(philo->race_ptr);
	finished = g_dead == FALSE && philo->must_eat != 0;
	pthread_mutex_unlock(philo->race_ptr);
	*/
	while (g_dead == FALSE && philo->must_eat != 0)
//	while (finished == TRUE)
	{
		thinking(philo);
		eating(philo);
		if (philo->must_eat == 0)
		{
			message(philo, "finished eating", FALSE);
			break ;
		}
		sleeping(philo);
		// LOCK philo->d_race
		// CHECK g_dead BEFORE 
		// UNLOCK philo->d_race
		/*
		pthread_mutex_lock(philo->race_ptr);
		finished = g_dead == FALSE && philo->must_eat != 0;
		pthread_mutex_unlock(philo->race_ptr);
		*/
	}
	if (philo->left_ptr != NULL)
		pthread_mutex_unlock(philo->left_ptr);
//	if (philo->right_ptr != NULL)
//		pthread_mutex_unlock(philo->right_ptr);
	pthread_mutex_unlock(philo->race_ptr);

	return (NULL);
}

int		start_all_threads(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&(philos + i)->thr, NULL, routine, philos + i)
				!= SUCCESS)
			return (display_ret_system_err(ER_THR_CREA, philos, n));
		if (i == 0)		// modif
			usleep(10);	// modif
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
		if (pthread_join((philos + i)->thr, NULL) == SUCCESS)
//			printf("joined thread %d\n", i);
			;
		else
			printf("couldn't join thread %d\n", i);
		i++;
	}
}
