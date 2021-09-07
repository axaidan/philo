#include "philosophers.h"

/*
void	*routine(void *param)
{
	t_philo				*philo;

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
	return (NULL);
}
*/

int	main(int argc, char *argv[])
{
	int			error;
	t_params	params;
	t_philo		*philos;
	//t_mutex		*mutexes;

	g_dead = 0;
	init_params(&params);
	error = parsing(argc, argv, &params);
	if (error)
		return (error);
	display_params(&params);
	philos = NULL;
	error = init_philos_array(params.n/*, &params*/, &philos);
	if (error)
		return (error);
	display_philos(philos, params.n);
	//set_zero_time();
	//launch_philos();
	//launch_watcher();
	destroy_all(philos, params.n);
	return (100);
}
