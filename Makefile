
## BUILD DETAILS

##CHANGE COMPILER AND MAKE

NAME 		=		pipex
BONUS 		=		pipex_bonus

CC 			= 		cc -g
## -Wall Wextra Werror
FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
RM 			=		rm
MAKE		=		make

## FOLDER PATH ##
INC_PATH	=		incs
SRC_PATH	=		srcs
COMMON_PATH	=		srcs_common
BASE_PATH	=		srcs_base
BONUS_PATH	=		srcs_bonus
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

SRCS_COMMON := 		$(addprefix $(SRC_PATH)/, $(addprefix $(COMMON_PATH)/, $(FILES_COMMON)))
SRCS_BASE 	:= 		$(addprefix $(SRC_PATH)/, $(addprefix $(BASE_PATH)/, $(FILES_BASE)))
SRCS_BONUS	:= 		$(addprefix $(SRC_PATH)/, $(addprefix $(BONUS_PATH)/, $(FILES_BONUS)))


OBJS_COMMON	=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS_COMMON))
OBJS_BASE	=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS_BASE))
OBJS_BONUS 	=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS_BONUS))

INCS		= 		-I$(INC_PATH) -I$(LIB_PATH)/$(LIB_INC_P)

all: $(NAME)

$(NAME): message $(LIBFT) $(OBJS_COMMON) $(OBJS_BASE)
	@$(CC) $(FLAGS) $(OBJS_COMMON) $(OBJS_BASE) $(INCS) -o $(NAME) $(ADD_LIB) $(LIB_PATH)/$(LIBFT)
	@echo Program $(NAME) ready!!

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

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
	@if [ -d "$(OBJ_PATH)" ]; then \
        rm -rf $(OBJ_PATH); \
    fi
	@make clean -C $(LIB_PATH)
	@echo Objects successfully deleted!

fclean: clean
	@echo Deleting libft.a...
	@if [ -n "$(wildcard  $(NAME))" ]; then \
        $(RM) $(NAME); \
    fi
	@if [ -n "$(wildcard  $(BONUS))" ]; then \
        $(RM) $(BONUS); \
    fi
	@if [ -n "$(wildcard  $(LIB_PATH)/$(LIBFT))" ]; then \
        $(RM) $(LIB_PATH)/$(LIBFT); \
    fi
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
