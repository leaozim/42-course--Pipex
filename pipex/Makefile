NAME			=	pipex

PRINTF_PATH		=	./my_libs/ft_printf/
LIBFT_PATH 		=	./my_libs/ft_libft/

PRINTF 			=	$(PRINTF_PATH)libftprintf.a
LIBFT 			=	$(LIBFT_PATH)libft.a

SRC_FILES 		=	pipex.c \
					init_pipex.c \
					command_checking.c \
					processes_pipe.c \
					handle_errors.c \
					utils.c

SRC_PATH		=	./srcs
OBJ_PATH		=	./obj

HSRC			=	./pipex.h 
SRC 			=	$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ 			=	$(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

CC				=	gcc
CFLAGS			=	-g3 -O3 -Wall -Wextra -Werror

RM				=	rm -rf

all:	$(NAME)

$(NAME):	$(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(OBJ) $(PRINTF) $(LIBFT) $(CFLAGS) -o $@ 

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC)  -c  $(CFLAGS)  $< -o $@

.c.o:
		$(CC)  -c  $(CFLAGS)  $< -o $@

$(PRINTF):
			make -C $(PRINTF_PATH)

$(LIBFT):
			make -C $(LIBFT_PATH)
			make bonus -C $(LIBFT_PATH)

clean:
			${RM} ${OBJ_PATH}
			cd $(PRINTF_PATH) && make clean 
			cd $(LIBFT_PATH) && make clean 

fclean:		clean
			${RM} ${NAME}
			${RM} ${PRINTF}
			${RM} ${LIBFT}

re:			fclean all

.PHONY:		all clean fclean re