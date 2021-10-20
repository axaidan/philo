#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*	STANDARD HEADER FILES */
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

/*	PROJECT HEADER FILES */
# include "structures.h"
# include "defines.h"

/*	!!! DEBUG.C !!! */
void	display_params(t_params *params);
void	display_philos(t_philo *philos_arr, int n);
int		check_fork_assignment(t_philo *philos, int n);

/*	parsing.c */
int		parsing(int argc, char **argv, t_params *params);

/*	errors.c */
int		display_ret_parsing_err(int error);
int		display_ret_system_err(int error, t_philo *philos, int n);
void	destroy_all(t_philo *philos, int n);

/*	initializations.c */
void	init_params(t_params *params);
int		init_philos_array(int n, t_params *params, t_philo **philos_ptr);

/*	actions.c */
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);

/*	display.c */
void	message(t_philo *philo, char *action, int dead);
void	text_display(int n, char *action);

/*	libft */
int		ft_atoi(const char *nptr);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int x, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

/*	time.c */
t_tstamp	get_timestamp(void);
//void		safe_sleep(t_tstamp until);
void		safe_sleep(t_tstamp until, t_philo *philo);

/*	threads.c */
void	join_all_threads(t_philo *philos, int n);
void	*routine(void *param);
int		start_all_threads(t_philo *philos, int n);

#endif
