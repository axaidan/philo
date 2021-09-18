#include "philosophers.h"

void	display(t_tstamp timestamp, int n, char *action)
{
	ft_putnbr_fd((int)timestamp, STDOUT_FILENO);
	ft_putstr_fd("\tphilo\t", STDOUT_FILENO);
	ft_putnbr_fd(n, STDOUT_FILENO);
	ft_putstr_fd("\tis\t", STDOUT_FILENO);
	ft_putendl_fd(action, STDOUT_FILENO);
}

void	message(t_philo *philo, char *action, t_tstamp timestamp)
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
//	printf("%10lu philo %4d is %s\n", timestamp, philo->n + 1, action);
	if (g_dead == FALSE)
	display(timestamp, philo->n, action);
	pthread_mutex_unlock(&msg_mutex);
	/*
	else if (die == TRUE)
	{
		pthread_mutex_lock(&msg_mutex);
//		printf("%10lu philo %4d is dead\n", timestamp, philo->n + 1);
		display(timestamp, philo->n, "dead");
		pthread_mutex_unlock(&msg_mutex);
		pthread_mutex_destroy(&msg_mutex);
	}
	*/
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

void	eat(t_philo *philo)
{
	long unsigned int	eat_ms_time;
	long unsigned int	wait_units;

	if (philo->forks < 2)
		return ;
	printf("%15lu philo %d is eating\n", get_timestamp(), philo->n);
	eat_ms_time = philo->args->eat;
	wait_units = eat_ms_time * 20;
	while (wait_units != 0)
	{
		usleep(50);
		wait_units--;
	}
}

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
