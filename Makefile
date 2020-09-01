SRCS	= main.c

OBJS	= ${SRCS:.c=.o}

NAME	= minirt.a
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
.c.o:
		${CC} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -sC ./minilibx_opengl/
			cp minilibx_opengl/libmlx.a .
			mv libmlx.a $(NAME)
			ar rc  ${NAME} ${OBJS}
			ranlib ${NAME}

run:
			@gcc  -lmlx -framework OpenGL -framework AppKit minirt.a & ./a.out

all:		${NAME}
clean:
			${RM} ${OBJS}
			${RM} ${NAME}
			make -sC ./minilibx_opengl/ clean
			
fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:	all fclean re