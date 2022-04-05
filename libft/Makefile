SRCS	= ft_strlen.c ft_strslen.c ft_split.c ft_atoi.c ft_htoi.c \
		  ft_freeints.c ft_freestrs.c ft_itoa.c \
		  ft_strchr.c ft_strdup.c ft_strtrimchr.c ft_strupdate.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

GCC		= gcc
#RM		= del
RM		= rm -rf
MAKELIB	= ar rc

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	${MAKELIB} ${NAME} ${OBJS}

all:	${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
