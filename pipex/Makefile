NAME			=	pipex

BONUS 			=	pipex_bonus

PRINTF_PATH		=	./my_libs/ft_printf/
LIBFT_PATH 		=	./my_libs/ft_libft/

PRINTF 			=	$(PRINTF_PATH)libftprintf.a
LIBFT 			=	$(LIBFT_PATH)libft.a

SRC_FILES 		=	pipex.c \
					init_pipex.c \
					cmd_checking.c \
					processes_pipe.c \
					handle_errors.c \
					utils.c

SRCB_FILES 		=	pipex_bonus.c \
					init_pipex_bonus.c \
					cmd_checking_bonus.c \
					processes_pipe_bonus.c \
					handle_errors_bonus.c \
					utils_bonus.c			

SRC_PATH		=	./srcs
OBJ_PATH		=	./obj
SRC_BONUS_PATH 	=	./srcs_bonus
OBJ_BONUS_PATH	=	./obj/bonus

HSRC			=	./pipex.h
HSRC_BONUS		=	./includes/pipex_bonus.h 
SRC 			=	$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ 			=	$(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC_BONUS 		=	$(addprefix $(SRC_BONUS_PATH)/, $(SRCB_FILES))
OBJ_BONUS 		=	$(SRC_BONUS:$(SRC_BONUS_PATH)/%.c=$(OBJ_BONUS_PATH)/%.o)

CC				=	gcc
CFLAGS			=	-g3 -O3 -Wall -Wextra -Werror

RM				=	rm -rf

all:	$(NAME)

bonus:
	@make OBJ="$(OBJ_BONUS)" all --no-print-directory

$(NAME):	$(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(OBJ) $(PRINTF) $(LIBFT) $(CFLAGS) -o $@ 

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC)  -c  $(CFLAGS)  $< -o $@

$(OBJ_BONUS_PATH)/%.o:	$(SRC_BONUS_PATH)/%.c
	@mkdir -p $(OBJ_BONUS_PATH)
	$(CC) -c $(CFLAGS) $< -o $@

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
			${RM} ${BONUS}

re:			fclean all

.PHONY:		all clean fclean re