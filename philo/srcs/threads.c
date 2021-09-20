#include "philosophers.h"

void    *routine(void *param)
{
    t_philo             *philo;

    philo = param;
    if (philo->n % 2 == 1)
        usleep(WAIT_UNIT_US);
	// else
	// 	thinking(philo);			// AVEC VAR last_state
    while (g_dead == FALSE)
    {
		//thinking(philo);
		eating(philo);
		sleeping(philo);
		/*
        think(philo);
        eat(philo);
        drop_forks(philo);
        sleeping(philo);
		*/
    }
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
		pthread_join((philos + i)->thr, NULL);
		//if (pthread_join((philos + i)->thr, NULL) == SUCCESS)
		//	printf("joined thread %d\n", i);
		i++;
	}
}
