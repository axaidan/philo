#include "philosophers.h"

void    *routine(void *param)
{
	// SET DEATH_TIME
	// START A LOOP CONTROLLING IF DEATH_TIME WAS REACHED
    t_philo             *philo;

    philo = param;
	message(philo, "born", get_timestamp(), FALSE);
	philo->death_time = philo->params->die;
/*
    if (philo->n % 2 == 1)
        think(philo);
    else
        usleep(WAIT_UNIT_US);
*/
    while (g_dead == FALSE)
    {
		if (get_timestamp() > philo->death_time)
			message(philo, NULL, get_timestamp(), TRUE);
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
		if (pthread_join((philos + i)->thr, NULL) == SUCCESS)
			printf("joined thread %d\n", i);
		i++;
	}
}
