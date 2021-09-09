#include "philosophers.h"

void    *routine(void *param)
{
    (void)param;
/*
    t_philo             *philo;

    philo = param;
    if (philo->n % 2 == 1)
        think(philo);
    else
        usleep(WAIT_UNIT_US);
    while (g_dead == 0)
    {
        think(philo);
        eat(philo);
        drop_forks(philo);
        sleeping(philo);
    }
*/
    return (NULL);
}


//void	start_all_threads()

void	join_all_threads(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join((philos + i)->thr, NULL);
		printf("joined thread %d\n", i);
		i++;
	}
}
