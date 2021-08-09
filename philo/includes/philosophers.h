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

/*	parsing.c */
int		parsing(int argc, char **argv, t_params *params);

/*	errors.c */
int		display_ret_err(int error);

/*	initializations.c */
void	init_params(t_params *params);

/*	libft */
int		ft_atoi(const char *nptr);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int x, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

#endif
