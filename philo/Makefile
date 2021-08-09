NAME		=	philosophers

# NAME MUST BE CHANGED BEFORE SUBMITTING

#B_NAME		=	pipex_bonus

SRCS		=	debug.c \
				main.c \
				parsing.c \
				errors.c \
				initializations.c \
				libft/ft_putstr_fd.c \
				libft/ft_putchar_fd.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr_fd.c \
				libft/ft_atoi.c \
				libft/ft_strncmp.c \
				libft/ft_isdigit.c \
				libft/ft_strlen.c

#B_SRCS		=	main_bonus.c \

OBJS		=	${addprefix srcs/, ${SRCS:.c=.o}}

#B_OBJS		=	${addprefix srcs/bonus/, ${B_SRCS:.c=.o}}

CC			=	gcc

E_FLAGS		=	-Wall -Werror -Wextra

I_FLD		=	includes/

I_FLAGS		=	-I ${I_FLD}

all			:	${NAME}


${NAME}		:	${OBJS}
			${CC} ${E_FLAGS} ${OBJS} -o ${NAME}

#bonus		:	${B_NAME}

#${B_NAME}	:	${B_OBJS}
#			${CC} ${E_FLAGS} ${B_OBJS} -o ${B_NAME}

%.o			:	%.c ${I_FLD}philosophers.h ${I_FLD}defines.h ${I_FLD}structures.h
			${CC} ${E_FLAGS} ${I_FLAGS} -c $< -o ${<:.c=.o}

clean		:
			rm -rf ${OBJS} ${B_OBJS}

fclean		:	clean
			rm -rf ${NAME} ${B_NAME}

re			:	fclean all

.PHONY		:	all re clean fclean
