#include "philosophers.h"

static int	check_empty(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (*(argv[i++]) == '\0')
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_digits(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j++]) == FALSE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_overflow(int argc, char **argv)
{
	int		i;
	size_t	len;

	i = 1;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len > 10)
			return (FAILURE);
		if (len == 10 && ft_strncmp("2147483647", argv[i], 10) < 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static void	get_values(int argc, char **argv, t_params *params)
{
	params->n = ft_atoi(argv[1]);
	params->die = ft_atoi(argv[2]);
	params->eat = ft_atoi(argv[3]);
	params->slp = ft_atoi(argv[4]);
	if (argc == 6)
		params->times = ft_atoi(argv[5]);
}

int	parsing(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
		return (display_ret_err(ER_ARGC));
	if (check_empty(argc, argv) == FAILURE)
		return (display_ret_err(ER_EMPTY));
	if (check_digits(argc, argv) == FAILURE)
		return (display_ret_err(ER_DIGIT));
	if (check_overflow(argc, argv) == FAILURE)
		return (display_ret_err(ER_OVFLW));
	get_values(argc, argv, params);
	// CHECK VALUES
	// lala
	return (SUCCESS);
}
