#ifndef DEFINES_H
# define DEFINES_H

/*	LOGICALS */
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1

/*	ERRORS */
enum e_errors
{
	ER_ARGC = 1,
	ER_EMPTY,
	ER_DIGIT,
	ER_OVFLW
};

#endif
