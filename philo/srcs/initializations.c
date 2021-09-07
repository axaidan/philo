#include "philosophers.h"

void	init_params(t_params *params)
{
	params->n = 0;
	params->die = 0;
	params->eat = 0;
	params->slp = 0;
	params->times = -1;
}

static void init_philo(t_philo *philo, int i)
{
	philo->thr = 0;
	philo->n = i;
	philo->forks = 0;
	philo->left_ptr = NULL;
	philo->right_ptr = NULL;
	philo->last_eat = 0;
	philo->death_time = 0;
	philo->must_eat = 0;
	philo->initialized = FALSE;
}

int		init_philos_array(int n/*, t_params *params*/, t_philo **philos_ptr)
{
	int	i;

	*philos_ptr = malloc(sizeof(t_philo) * n);
	if (*philos_ptr == NULL)
		return (display_ret_system_err(ER_ARR_ALC, *philos_ptr, n));
	i = 0;
	while (i < n)
	{
		init_philo(*philos_ptr + i, i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&(*philos_ptr + i)->left, NULL) != SUCCESS)
			return (display_ret_system_err(ER_MUT_INIT, *philos_ptr, n));
		(*philos_ptr + i++)->initialized = TRUE;
	}
	return (SUCCESS);
}
