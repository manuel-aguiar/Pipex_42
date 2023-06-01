
## BUILD DETAILS

##CHANGE COMPILER AND MAKE

NAME 		=		pipex
BONUS 		=		pipex

CC 			= 		gcc
## -Wall Wextra Werror
FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
RM 			=		rm
MAKE		=		mingw32-make

## FOLDER PATH ##
INC_PATH	=		incs
SRC_CMN_PATH	=	srcs_common
SRC_BASE_PATH	=	srcs_base
BONUS_PATH	=		bonus
OBJ_PATH	=		objs

LIB_PATH	=		libft
LIB_INC_P	=		incs

## SOURCE LIBRARIES
LIBFT		=		libft.a

## SOURCE FILES ##
FILES_COMMON	=	pipex_struct.c		\
					pipex_input.c		\
					pipex_tempfile.c	\
					pipex_process.c		\
					pipex_exec.c		\
					pipex_error_msg.c

FILES_BASE	=		pipex_main_base.c

FILES_BONUS	=		pipex_main_bonus.c

SRCS_COMMON := 		$(addprefix $(SRC_CMN_PATH)/, $(FILES_COMMON))
SRCS_BASE 	:= 		$(addprefix $(SRC_BASE_PATH)/, $(FILES_BASE))
SRCS_BONUS	:= 		$(addprefix $(BONUS_PATH)/, $(FILES_BONUS))


OBJS_COMMON	=		$(SRCS_COMMON:%.c=%.o)
OBJS_BASE	=		$(SRCS_BASE:%.c=%.o)
OBJS_BONUS 	=		$(SRCS_BONUS:%.c=%.o)

INCS		= 		-I$(INC_PATH) -I$(LIB_PATH)/$(LIB_INC_P)

all: $(NAME)
##@mkdir -p objs
##@mv $(OBJS) objs
##@mv $(OBJS_PS) objs

$(NAME): message $(LIBFT) $(OBJS_COMMON) $(OBJS_BASE)
	@$(CC) $(FLAGS) $(OBJS_COMMON) $(OBJS_BASE) $(INCS) -o $(NAME) $(ADD_LIB) $(LIB_PATH)/$(LIBFT)
	@echo Program $(NAME) ready!!

%.o : %.c
	@$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@echo Preparing Libft....
	@$(MAKE) -C $(LIB_PATH)

bonus: $(BONUS)

$(BONUS) : message $(LIBFT) $(OBJS_COMMON) $(OBJS_BONUS)
	@$(CC) $(FLAGS) $(OBJS_COMMON) $(OBJS_BONUS) $(INCS) -o $(BONUS) $(ADD_LIB) $(LIB_PATH)/$(LIBFT)
	@echo Program $(BONUS) ready!!

message:
	@echo Building program....

clean:
	@echo Removing object files.....
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_PATH)
	@rmdir $(OBJ_PATH)
	@echo Objects successfully deleted!

fclean: clean
	@echo Deleting libft.a...
	$(RM) $(NAME)
	@echo Done!!

re: fclean all

.PHONY: clean fclean re message bonus

##COLOUR

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
