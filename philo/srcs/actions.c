#include "philosophers.h"

void	text_display(int n, char *action)
{
	ft_putnbr_fd((int)get_timestamp(), STDOUT_FILENO);
	ft_putstr_fd("\t\tphilo\t", STDOUT_FILENO);
	ft_putnbr_fd(n, STDOUT_FILENO);
	ft_putchar_fd('\t', STDOUT_FILENO);
	ft_putendl_fd(action, STDOUT_FILENO);
}

void	message(t_philo *philo, char *action, int dead)
{
	static int		first = TRUE;
	static t_mutex	msg_mutex;

	if (first == TRUE)
	{
		first = FALSE;
		if (pthread_mutex_init(&msg_mutex, NULL) != SUCCESS)
			printf("message mutex initialization error\n");
	}
	pthread_mutex_lock(&msg_mutex);
	if (g_dead == FALSE || dead == TRUE)
		text_display(philo->n + 1, action);
	pthread_mutex_unlock(&msg_mutex);
}

void	thinking(t_philo *philo)
{
	if ((philo->last_state != SLEPT && philo->last_state != BORN)
			|| philo->forks != 0)
		return ;
	philo->last_state = THOUGHT;
	if (philo->n % 2 == 0)
	{
		if (philo->right_ptr != NULL)
		{
			pthread_mutex_lock(philo->right_ptr);
			message(philo, "has taken R fork", FALSE);
			philo->forks++;
		}
		if (philo->left_ptr != NULL)
		{
			pthread_mutex_lock(philo->left_ptr);
			message(philo, "has taken L fork", FALSE);
			philo->forks++;
		}
	}
	else
	{
		if (philo->left_ptr != NULL)
		{
			pthread_mutex_lock(philo->left_ptr);
			message(philo, "has taken L fork", FALSE);
			philo->forks++;
		}
		if (philo->right_ptr != NULL)
		{
			pthread_mutex_lock(philo->right_ptr);
			message(philo, "has taken R fork", FALSE);
			philo->forks++;
		}
	}
}

void	eating(t_philo *philo)
{
	t_tstamp	timestamp;

	if (philo->last_state != THOUGHT || philo->forks != 2)
		return ;
	philo->last_state = ATE;
	timestamp = get_timestamp();
	philo->death_time = timestamp + philo->params->die;
	message(philo, "is eating", FALSE);
	safe_sleep(timestamp + philo->params->eat);
	if (philo->must_eat != -1)
		philo->must_eat--;
	if (philo->right_ptr != NULL)
	{
		pthread_mutex_unlock(philo->right_ptr);
		philo->forks--;
	}
	if (philo->left_ptr != NULL)
	{
		pthread_mutex_unlock(philo->left_ptr);
		philo->forks--;
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->last_state != ATE || philo->forks != 0)
		return ;
	philo->last_state = SLEPT;
	message(philo, "is sleeping", FALSE);
	safe_sleep(get_timestamp() + philo->params->slp);
	message(philo, "is thinking", FALSE);
}
