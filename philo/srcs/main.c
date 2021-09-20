#include "philosophers.h"

void	watcher(t_philo *philos, int n)
{
	int			i;
	t_tstamp	timestamp;

	i = 0;
	while (i < n)
	{
		timestamp = get_timestamp();
		if (timestamp >= (philos + i)->death_time)
		{
			g_dead = TRUE;
			message(philos + i, "died", TRUE);
			return ;
		}
		i++;
		if (i == n)
			i = 0;
	}
}

int	main(int argc, char *argv[])
{
	int			error;
	t_params	params;
	t_philo		*philos;

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
	get_timestamp();	// SET ZERO
	error = start_all_threads(philos, params.n);
	if (error)
		return (error);
	watcher(philos, params.n);
	join_all_threads(philos, params.n);
	destroy_all(philos, params.n);
	return (100);
}
