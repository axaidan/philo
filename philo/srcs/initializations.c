#include "philosophers.h"

void	init_params(t_params *params)
{
	params->n = 0;
	params->die = 0;
	params->eat = 0;
	params->slp = 0;
	params->times = -1;
}

static void init_philo(t_philo *philo, int i, t_params *params)
{
	philo->thr = 0;
	philo->n = i;
	philo->forks = 0;
	philo->left_ptr = NULL;
	philo->right_ptr = NULL;
	philo->last_eat = 0;
	philo->death_time = 0;
	philo->must_eat = 0;
	philo->m_init = FALSE;
	philo->t_init = FALSE;
	philo->params = params;
}

int		check_fork_assignment(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i == 0)
		{
			if (philos->right_ptr == (philos + n - 1)->left_ptr)
				printf("philos 0 and n share a fork\n");
			else
				printf("philos 0 and n don't share a fork\n");
		}
		else
		{
			if ((philos + i)->right_ptr == (philos + i - 1)->left_ptr)
				printf("philos %d and %d share a fork\n", i, i - 1);
			else
				printf("philos %d and %d don't share a fork\n", i, i - 1);
		}
		i++;
	}
	return (SUCCESS);
}

int		init_philos_array(int n, t_params *params, t_philo **philos_ptr)
{
	int	i;

	*philos_ptr = malloc(sizeof(t_philo) * n);
	if (*philos_ptr == NULL)
		return (display_ret_system_err(ER_ARR_ALC, *philos_ptr, n));
	i = 0;
	while (i < n)
	{
		init_philo(*philos_ptr + i, i, params);
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&(*philos_ptr + i)->left, NULL) != SUCCESS)
			return (display_ret_system_err(ER_MUT_INIT, *philos_ptr, n));
		(*philos_ptr + i)->m_init = TRUE;
		(*philos_ptr + i)->left_ptr = &(*philos_ptr + i)->left;
		if (i > 0)
			(*philos_ptr + i)->right_ptr = (*philos_ptr + i - 1)->left_ptr;
		i++;
	}
	(*philos_ptr)->right_ptr = (*philos_ptr + i - 1)->left_ptr;
	check_fork_assignment(*philos_ptr, n);
	return (SUCCESS);
}
