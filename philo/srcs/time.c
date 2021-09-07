#include "philosophers.h"

long unsigned int   get_timestamp(void)
{
	static int			first = TRUE;
	static t_timeval	zero;
	long unsigned int	timestamp;
	t_timeval			calculation;
	t_timeval			now;

	if (first == TRUE)
	{
		first = FALSE;
		gettimeofday(&zero, NULL);
	}
	gettimeofday(&now, NULL);
	calculation.tv_sec = now.tv_sec - zero.tv_sec;
	timestamp = calculation.tv_sec * 1000 + (now.tv_usec - zero.tv_usec) / 1000;
	return (timestamp);
}
