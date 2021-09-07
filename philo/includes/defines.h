#ifndef DEFINES_H
# define DEFINES_H

# define WAIT_UNIT_US 300

/*	LOGICALS */
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1

/*	ERRORS */
enum	e_errors
{
	ER_ARGC = 1,
	ER_EMPTY,
	ER_DIGIT,
	ER_OVFLW,
	ER_VALUE,
	ER_ARR_ALC,
	ER_MUT_INIT
};

enum	e_state
{
	WAITING = -1,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

#endif
