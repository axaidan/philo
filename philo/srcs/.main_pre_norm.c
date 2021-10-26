#include "philosophers.h"

void	watcher(t_philo *philos, int n, int *death)
{
	int			i;
	int			fully_ate;
	int			finished;
	int			eating_continues;	
	t_tstamp	timestamp;

	fully_ate = 0;
	i = 0;
	finished = FALSE;
	while (finished == FALSE && i < n)
	{
		timestamp = get_timestamp();

		pthread_mutex_lock((philos + i)->race_ptr);
		eating_continues = (philos + i)->must_eat != 0;
		finished = timestamp >= (philos + i)->death_time && eating_continues;
		pthread_mutex_unlock((philos + i)->race_ptr);
		if (finished)
		{
			pthread_mutex_lock(&(philos + i)->params->death_mutex);
			*death = TRUE;
			pthread_mutex_unlock(&(philos + i)->params->death_mutex);
			message(philos + i, "died", TRUE, FALSE);
		//	pthread_mutex_unlock((philos + i)->race_ptr);
			return ;
		}
		else if (eating_continues == FALSE)
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
	message(NULL, NULL, FALSE, FALSE);	// INIT static t_mutex msg_mutex;
	get_timestamp();					// SET ZERO
	error = start_all_threads(philos, params.n);
	if (error)
		return (error);
	watcher(philos, params.n, &params.death);
	join_all_threads(philos, params.n);
	destroy_all(philos, params.n);
	return (SUCCESS);
}
