#include "philosophers.h"

void    text_display(int n, char *action)
{
	ft_putnbr_fd((int)get_timestamp(), STDOUT_FILENO);
	ft_putstr_fd("\t\tphilo\t", STDOUT_FILENO);
	ft_putnbr_fd(n, STDOUT_FILENO);
	ft_putchar_fd('\t', STDOUT_FILENO);
	ft_putendl_fd(action, STDOUT_FILENO);
}

void    message(t_philo *philo, char *action, int dead)
{
	static int      first = TRUE;
	static t_mutex  msg_mutex;

	if (first == TRUE)
	{
		first = FALSE;
		if (pthread_mutex_init(&msg_mutex, NULL) != SUCCESS)
			printf("message mutex initialization error\n");
		return ;
	}
	pthread_mutex_lock(&msg_mutex);
	if (g_dead == FALSE || dead == TRUE)
		text_display(philo->n + 1, action);
	pthread_mutex_unlock(&msg_mutex);
}

