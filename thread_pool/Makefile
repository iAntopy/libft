
SRC_DIR		= src/

_SRC		:=	thpool_init.c			\
			thpool_submit.c			\
			thpool_destroy.c		\
			thpool_task_handler.c		\
			thpool_task_queue_utils.c	\
			thpool_print.c			\
			thpool_error_handling.c 	\
			ft_utils.c			\
			malloc_free.c			\
			ft_printf.c			\
			ft_eprintf.c

SRCS		= $(addprefix $(SRC_DIR), $(_SRC))

OBJS		= $(SRCS:.c=.o)

INCL		= incl/

CC		= gcc
CFLAGS		= -g -pthread -Wall -Wextra -Werror -O2

AR		= ar -rcs

NAME		= libthpool.a

%.o:		%.c
		-$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
		$(AR) $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:			fclean all
