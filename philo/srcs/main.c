#include "philosophers.h"

int	g_dead;

void	watcher(t_philo *philos, int n)
{
	int			i;
	int			fully_ate;
	int			finished;
	t_tstamp	timestamp;

	fully_ate = 0;
	i = 0;
	finished = FALSE;
	while (finished == FALSE && i < n)
	{
		pthread_mutex_lock((philos + i)->left_ptr);
		timestamp = get_timestamp();
//		if (timestamp >= (philos + i)->death_time && (philos + i)->must_eat != 0)
		finished = timestamp >= (philos + i)->death_time && (philos + i)->must_eat != 0;
		pthread_mutex_unlock((philos + i)->left_ptr);
		if (finished)
		{
			g_dead = TRUE;
			message(philos + i, "died", TRUE);
			return ;
		}
		else if ((philos + i)->must_eat == 0)
			fully_ate++;
		i++;
		if (i == n)
		{
			i = 0;
			if (fully_ate < n)
				fully_ate = 0;
			else
				return ;
		}
	}
}

int	main(int argc, char *argv[])
{
	int			error;
	t_params	params;
	t_philo		*philos;

	printf("sizeof(t_mutex) = %lu\n", sizeof(t_mutex));
	printf("sizeof(t_thread) = %lu\n", sizeof(t_thread));
	g_dead = FALSE;
	init_params(&params);
	error = parsing(argc, argv, &params);
	if (error)
		return (error);
	display_params(&params);
	philos = NULL;
	error = init_philos_array(params.n, &params, &philos);
	if (error)
		return (error);
	//	display_philos(philos, params.n);
	message(NULL, NULL, FALSE);
	get_timestamp();	// SET ZERO
	error = start_all_threads(philos, params.n);
	if (error)
		return (error);
	watcher(philos, params.n);
	join_all_threads(philos, params.n);
	destroy_all(philos, params.n);
	return (100);
}
