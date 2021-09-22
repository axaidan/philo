#include "philosophers.h"

void	display_params(t_params *params)
{
	printf("n\t=\t%10d\n", params->n);
	printf("die\t=\t%10d\n", params->die);
	printf("eat\t=\t%10d\n", params->eat);
	printf("slp\t=\t%10d\n", params->slp);
	printf("times\t=\t%10d\n", params->times);
}

void	display_philos(t_philo *philos_arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("philo %d\n", philos_arr[i].n);
		i++;
	}	
}

int     check_fork_assignment(t_philo *philos, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (i == n - 1)
		{
			if ((philos + i)->right_ptr == philos->left_ptr)
				;
//				printf("philos\t%d\tand\t%d\tshare a fork\n", i + 1, 1);
			else
			{
				printf("philos\t%d\tand\t%d\tdon't share a fork\n", i + 1, 1);
				return (FALSE);
			}
		}
		else
		{
			if ((philos + i)->right_ptr == (philos + i + 1)->left_ptr)
				;
//				printf("philos\t%d\tand\t%d\tshare a fork\n", i + 1, i + 2);
			else
			{
				printf("philos\t%d\tand\t%d\tdon't share a fork\n", i + 1, i + 2);
				return (FALSE);
			}
		}
		i++;
	}
	return (SUCCESS);
}
