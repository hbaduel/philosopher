NAME = philo

SRC = srcs/main.c srcs/utils.c srcs/thread.c srcs/init.c srcs/second_utils.c

OBJS = ${SRC:%.c=%.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

${NAME}: ${OBJS}
	${CC} ${FLAGS} -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.phony: all clean fclean re
