# NAME MUST BE CHANGED BEFORE SUBMITTING
NAME		=	philosophers

SRCS		=	debug.c \
				main.c \
				parsing.c \
				errors.c \
				initializations.c \
				time.c \
				threads.c \
				actions.c \
				display.c \
				libft/ft_putstr_fd.c \
				libft/ft_putchar_fd.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr_fd.c \
				libft/ft_atoi.c \
				libft/ft_strncmp.c \
				libft/ft_isdigit.c \
				libft/ft_strlen.c

OBJS		=	${addprefix srcs/, ${SRCS:.c=.o}}

CC			=	gcc

#E_FLAGS		=	-Wall -Werror -Wextra 
E_FLAGS		=	-Wall -Werror -Wextra -g -fsanitize=thread

I_FLD		=	includes/

I_FLAGS		=	-I ${I_FLD}

all			:	${NAME}
			@echo "====================================================="
			@echo "DON'T FORGET TO CHANGE PROGRAM NAME BEFORE SUBMITTING"
			@echo "====================================================="


${NAME}		:	${OBJS}
			${CC} ${E_FLAGS} ${OBJS} -o ${NAME} -lpthread

%.o			:	%.c ${I_FLD}philosophers.h ${I_FLD}defines.h ${I_FLD}structures.h
			${CC} ${E_FLAGS} ${I_FLAGS} -c $< -o ${<:.c=.o}

clean		:
			rm -rf ${OBJS} ${B_OBJS}

fclean		:	clean
			rm -rf ${NAME} ${B_NAME}

re			:	fclean all

.PHONY		:	all re clean fclean
