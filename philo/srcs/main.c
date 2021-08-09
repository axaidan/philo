#include "philosophers.h"

int	main(int argc, char *argv[])
{
	int			error;
	t_params	params;

	init_params(&params);
	error = parsing(argc, argv, &params);
	if (error)
		return (error);
	display_params(&params);
	return (0);
}
