SRCS	= main.c

OBJS	= ${SRCS:.c=.o}

NAME	= minirt.a
CC		= cc
RM		= rm -f
# CFLAGS	= -Wall -Werror -Wextra
.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -sC ./minilibx_mms/
			cp minilibx_opengl/libmlx.a .
			mv libmlx.a.a $(NAME)
			ar rc  ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}
clean:
			${RM} ${OBJS}
			make -sC ./minilibx_opengl/ clean
fclean:		clean
			${RM} ${NAME}
			make -sC ./minilibx_opengl/ fclean

re:			fclean all

.PHONY:	all fclean re