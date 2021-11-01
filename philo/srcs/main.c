#include "philosophers.h"

static int	reset_counters(int *i, int *fully_ate, int n)
{
	*i = 0;
	if (*fully_ate < n)
		*fully_ate = 0;
	else
		return (FAILURE);
	return (SUCCESS);
}

static void	set_and_display_death(t_philo *philos, int i, int *death)
{
	pthread_mutex_lock(&(philos + i)->params->death_mutex);
	*death = TRUE;
	pthread_mutex_unlock(&(philos + i)->params->death_mutex);
	message(philos + i, "died", TRUE, FALSE);
}

static void	check_philo_values(t_philo *philos, int i, int *finished,
		int *eating_continues)
{
	t_tstamp	timestamp;

	timestamp = get_timestamp();
	pthread_mutex_lock((philos + i)->race_ptr);
	*eating_continues = (philos + i)->must_eat != 0;
	*finished = timestamp >= (philos + i)->death_time && *eating_continues;
	pthread_mutex_unlock((philos + i)->race_ptr);
}

void	watcher(t_philo *philos, int n, int *death)
{
	int			i;
	int			fully_ate;
	int			finished;
	int			eating_continues;	

	fully_ate = 0;
	i = 0;
	finished = FALSE;
	while (finished == FALSE && i < n)
	{
		check_philo_values(philos, i, &finished, &eating_continues);
		if (finished)
		{
			set_and_display_death(philos, i, death);
			return ;
		}
		else if (eating_continues == FALSE)
			fully_ate++;
		i++;
		if (i == n && reset_counters(&i, &fully_ate, n) == FAILURE)
			return ;
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
	philos = NULL;
	error = init_philos_array(params.n, &params, &philos);
	if (error)
		return (error);
	message(NULL, NULL, FALSE, FALSE);
	get_timestamp();
	error = start_all_threads(philos, params.n);
	if (error)
		return (error);
	watcher(philos, params.n, &params.death);
	join_all_threads(philos, params.n);
	destroy_all(philos, params.n);
	return (SUCCESS);
}
