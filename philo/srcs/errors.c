#include "philosophers.h"

void	destroy_all(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n && (philos + i)->m_init == TRUE)
	{
		pthread_mutex_destroy(&(philos + i)->left);
		pthread_mutex_destroy((philos + i)->race_ptr);
		i++;
	}
	pthread_mutex_destroy(&philos->params->death_mutex);
	message(NULL, NULL, FALSE, TRUE);
	free(philos);
}

int	display_ret_parsing_err(int error)
{
	if (error)
	{
		ft_putstr_fd("philo: argument error: ", STDERR_FILENO);
		if (error == ER_ARGC)
			ft_putendl_fd("takes 4 or 5 arguments", STDERR_FILENO);
		else if (error == ER_EMPTY)
			ft_putendl_fd("argument cannot be empty", STDERR_FILENO);
		else if (error == ER_DIGIT || error == ER_VALUE)
			ft_putendl_fd("all arguments must be non-null positive integers",
				STDERR_FILENO);
		else if (error == ER_OVFLW)
			ft_putendl_fd("positive integers go up to 2,147,483,647",
				STDERR_FILENO);
	}
	return (error);
}

int	display_ret_system_err(int error, t_philo *philos, int n)
{
	if (error)
	{
		ft_putstr_fd("philo: system error: ", STDERR_FILENO);
		if (error == ER_ARR_ALC)
			ft_putendl_fd("could not allocate philosophers array",
				STDERR_FILENO);
		else if (error == ER_MUT_INIT)
			ft_putendl_fd("could not initialize a mutex",
				STDERR_FILENO);
		else if (error == ER_THR_CREA)
			ft_putendl_fd("could not create a new thread", STDERR_FILENO);
	}
	join_all_threads(philos, philos->params->n);
	destroy_all(philos, n);
	return (error);
}
