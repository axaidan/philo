#include "philosophers.h"

void	text_display(int n, char *action)
{
	ft_putnbr_fd((int)get_timestamp(), STDOUT_FILENO);
	ft_putstr_fd("\t\tphilo\t", STDOUT_FILENO);
	ft_putnbr_fd(n, STDOUT_FILENO);
	ft_putchar_fd('\t', STDOUT_FILENO);
	ft_putendl_fd(action, STDOUT_FILENO);
}

//void	message(t_philo *philo, char *action, t_tstamp timestamp, int dead)
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
//		text_display(timestamp, philo->n + 1, action);
		text_display(philo->n + 1, action);
	pthread_mutex_unlock(&msg_mutex);
}

void	eating(t_philo *philo)
{
	t_tstamp	timestamp;

	pthread_mutex_lock(philo->left_ptr);
	message(philo, "has taken L fork", FALSE);
	pthread_mutex_lock(philo->right_ptr);
	message(philo, "has taken R fork", FALSE);
	timestamp = get_timestamp();
	philo->death_time = timestamp + philo->params->die;
	message(philo, "is eating", FALSE);
	safe_sleep(timestamp + philo->params->eat);
	pthread_mutex_unlock(philo->right_ptr);
	pthread_mutex_unlock(philo->left_ptr);
}

void	sleeping(t_philo *philo)
{
	message(philo, "is sleeping", FALSE);
	safe_sleep(get_timestamp() + philo->params->slp);
	message(philo, "is thinking", FALSE);
}
