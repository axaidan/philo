#include "philosophers.h"

void    *routine(void *param)
{
	t_philo             *philo;

	philo = param;
	if (philo->n % 2 == 0)
		thinking(philo);
	else
		usleep(WAIT_UNIT_US);
	while (g_dead == FALSE && philo->must_eat != 0)
	{
		thinking(philo);
		eating(philo);
		if (philo->must_eat == 0)
		{
			message(philo, "finished eating", FALSE);
			break ;
		}
		sleeping(philo);
	}
	if (philo->left_ptr != NULL)
		pthread_mutex_unlock(philo->left_ptr);
	if (philo->right_ptr != NULL)
		pthread_mutex_unlock(philo->right_ptr);
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
			//printf("joined thread %d\n", i);
			;
		else
			printf("couldn't join thread %d\n", i);
		i++;
	}
}
