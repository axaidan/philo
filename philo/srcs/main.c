#include "philosophers.h"

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
	start_all_threads(philos, params.n);
	join_all_threads(philos, params.n);
	destroy_all(philos, params.n);
	return (100);
}