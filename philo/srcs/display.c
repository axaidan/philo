#include "philosophers.h"

void	text_display(int n, char *action)
{
	ft_putnbr_fd((int)get_timestamp(), STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putnbr_fd(n, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putendl_fd(action, STDOUT_FILENO);
}

void	message(t_philo *philo, char *action, int dead, int shutdown)
{
	static int		first = TRUE;
	static t_mutex	msg_mutex;

	if (first == TRUE || shutdown == TRUE)
	{
		if (first == TRUE)
		{
			first = FALSE;
			if (pthread_mutex_init(&msg_mutex, NULL) != SUCCESS)
				printf("message mutex initialization error\n");
		}
		else
			pthread_mutex_destroy(&msg_mutex);
		return ;
	}
	if (death_occured(philo) == FALSE || dead == TRUE)
	{
		pthread_mutex_lock(&msg_mutex);
		text_display(philo->n + 1, action);
		pthread_mutex_unlock(&msg_mutex);
	}
}
