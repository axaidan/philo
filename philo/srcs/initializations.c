#include "philosophers.h"

void	init_params(t_params *params)
{
	params->n = 0;
	params->die = 0;
	params->eat = 0;
	params->slp = 0;
	params->times = -1;
	params->death = FALSE;
}

static void	init_philo(t_philo *philo, int i, t_params *params)
{
	philo->thr = 0;
	philo->n = i;
	philo->left_ptr = NULL;
	philo->right_ptr = NULL;
	philo->last_eat = 0;
	philo->death_time = params->die;
	philo->must_eat = params->times;
	philo->m_init = FALSE;
	philo->t_init = FALSE;
	philo->params = params;
	philo->race_ptr = NULL;
}

static int	init_and_grab_own_fork(t_philo **philos_ptr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&(*philos_ptr + i)->left, NULL) != SUCCESS)
			return (display_ret_system_err(ER_MUT_INIT, *philos_ptr, n));
		if (pthread_mutex_init(&(*philos_ptr + i)->d_race, NULL) != SUCCESS)
			return (display_ret_system_err(ER_MUT_INIT, *philos_ptr, n));
		(*philos_ptr + i)->m_init = TRUE;
		(*philos_ptr + i)->left_ptr = &(*philos_ptr + i)->left;
		(*philos_ptr + i)->race_ptr = &(*philos_ptr + i)->d_race;
		i++;
	}
	return (SUCCESS);
}

static void	grab_neighbor_s_fork(t_philo **philos_ptr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i < n - 1)
			(*philos_ptr + i)->right_ptr = (*philos_ptr + i + 1)->left_ptr;
		i++;
	}
	(*philos_ptr + n - 1)->right_ptr = (*philos_ptr)->left_ptr;
}

int	init_philos_array(int n, t_params *params, t_philo **philos_ptr)
{
	int	i;
	int	error;

	if (pthread_mutex_init(&params->death_mutex, NULL) != SUCCESS)
		return (display_ret_system_err(ER_MUT_INIT, *philos_ptr, n));
	*philos_ptr = malloc(sizeof(t_philo) * n);
	if (*philos_ptr == NULL)
		return (display_ret_system_err(ER_ARR_ALC, *philos_ptr, n));
	i = 0;
	while (i < n)
	{
		init_philo(*philos_ptr + i, i, params);
		i++;
	}
	error = init_and_grab_own_fork(philos_ptr, n);
	if (error)
		return (error);
	if (n == 1)
		return (SUCCESS);
	grab_neighbor_s_fork(philos_ptr, n);
	return (SUCCESS);
}
