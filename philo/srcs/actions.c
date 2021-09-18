#include "philosophers.h"

void	display(t_tstamp timestamp, int n, char *action)
{
	ft_putnbr_fd((int)timestamp, STDOUT_FILENO);
	ft_putstr_fd("\t\tphilo\t", STDOUT_FILENO);
	ft_putnbr_fd(n, STDOUT_FILENO);
	ft_putchar_fd('\t', STDOUT_FILENO);
	ft_putendl_fd(action, STDOUT_FILENO);
}

void	message(t_philo *philo, char *action, t_tstamp timestamp, int dead)
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
		display(timestamp, philo->n + 1, action);
	pthread_mutex_unlock(&msg_mutex);
}

/*
void	think(t_philo *philo)
{
	if (philo->forks == 2)
		return ;
   printf("%15lu philo %d is thinking\n", get_timestamp(), philo->n);
   while (philo->forks < 2)
   {
	   if (fork1 == FALSE && philo->forks < 2)
			grab_fork1(philo);
	   if (fork2 == FALSE && philo->forks < 2)
	   		grab_fork2(philo);
	}
}
*/

void	eating(t_philo *philo)
{
	t_tstamp	timestamp;

	pthread_mutex_lock(philo->left_ptr);
	message(philo, "has taken L fork", get_timestamp(), FALSE);
	pthread_mutex_lock(philo->right_ptr);
	message(philo, "has taken R fork", get_timestamp(), FALSE);
	timestamp = get_timestamp();
	philo->death_time = timestamp + philo->params->die;
	message(philo, "is eating", timestamp, FALSE);
	safe_sleep(timestamp + philo->params->eat);
	pthread_mutex_unlock(philo->right_ptr);
	pthread_mutex_unlock(philo->left_ptr);
}

void	sleeping(t_philo *philo)
{
	message(philo, "is sleeping", get_timestamp(), FALSE);
	safe_sleep(get_timestamp() + philo->params->slp);
	message(philo, "is thinking", get_timestamp(), FALSE);
}

/*
void	drop_forks(t_philo *philo)
{
	if (philo->forks < 2)
		return ;
	philo->forks = 0;
}

void	sleeping(t_philo *philo)
{
	long unsigned int	sleep_ms_time;

	if (philo->forks != 0)
		return ;
	printf("%15lu philo %d is sleeping\n", get_timestamp(), philo->n);
	sleep_ms_time = philo->args->slp;	
	usleep(sleep_ms_time * 1000);
}
*/
