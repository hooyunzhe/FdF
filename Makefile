NAME	= fdf

SDIR	= src
ODIR	= obj
LDIR	= libft

SRCS_F	= fdf.c read.c map.c draw.c hud.c utils.c get_next_line.c

OBJS_F	= ${addprefix ${ODIR}/, ${SRCS_F:.c=.o}}

GCC		= gcc
RM		= rm -f

LIBFT	= libft.a

LIBMLX	= -Lmlx -lmlx

CFLAGS	= -Wall -Wextra -Werror

MFLAGS	= -framework OpenGL -framework AppKit

all:	${NAME}

${ODIR}/%.o:	${SDIR}/%.c
	${GCC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	make -C ${LDIR}

${NAME}:	${LIBFT} ${OBJS_F} ${OBJS_L}
	${GCC} ${LIBMLX} ${MFLAGS} -o ${NAME} ${OBJS_F} ${LDIR}/${LIBFT}

clean:
	${RM} ${OBJS_F}
	make clean -C ${LDIR}

fclean:
	${RM} ${NAME}
	${RM} ${OBJS_F}
	make fclean -C ${LDIR}

re:	fclean all

.PHONY:	all clean fclean re