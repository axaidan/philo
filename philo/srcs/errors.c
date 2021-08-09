#include "philosophers.h"

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
