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
