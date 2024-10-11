NAME        := pipex
NAME_B		:= pipex_bonus
CC        := cc
FLAGS    := -Wall -Wextra -Werror
MAIN_M		:=		pipex.c
MAIN_B		:=		pipex_bonus.c
SRCS        :=      ft_toupper.c \
                          ft_tolower.c \
                          ft_split.c \
                          ft_memcpy.c \
                          ft_lstsize.c \
                          ft_strnstr.c \
                          ft_isalnum.c \
                          ft_strlcat.c \
                          ft_strchr.c \
                          ft_lstiter.c \
                          ft_isdigit.c \
                          ft_itoa.c \
                          ft_lstclear.c \
                          ft_strlcpy.c \
                          ft_strrchr.c \
                          ft_isprint.c \
                          ft_isascii.c \
                          ft_lstadd_front.c \
                          ft_strjoin.c \
                          ft_lstmap.c \
                          ft_striteri.c \
                          ft_strncmp.c \
                          ft_putchar_fd.c \
                          ft_memset.c \
                          ft_strlen.c \
                          ft_atoi.c \
                          ft_strmapi.c \
                          ft_lstlast.c \
                          ft_bzero.c \
                          ft_substr.c \
                          ft_putstr_fd.c \
                          ft_strdup.c \
                          ft_isalpha.c \
                          ft_lstdelone.c \
                          ft_lstnew.c \
                          ft_memchr.c \
                          ft_memmove.c \
                          ft_lstadd_back.c \
                          ft_putendl_fd.c \
                          ft_putnbr_fd.c \
                          ft_strtrim.c \
                          ft_memcmp.c \
                          ft_calloc.c \
                          utils.c
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} ${MAIN_M} -o ${NAME} ${OBJS}
			clear
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."		
			${CC} ${FLAGS} ${MAIN_B} -o ${NAME_B} ${OBJS}
			clear
			@echo "$(GREEN)$(NAME_B) created[0m ✔️"

clean:
			@ ${RM} *.o
			clear
			@ echo "$(RED)Deleting $(CYAN)pipex $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME} ${NAME_B}
			clear
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)and $(CYAN)$(NAME_B) $(CLR_RMV)✔️"

re:			fclean all

fast:		all bonus clean
			clear
			@ echo "$(CYAN)You can test programs ✔️"
			
push:
			git add .
			git	commit -m "def"
			git push
			clear
			@ echo "$(CYAN)All files in this directory have been pushed successfully ✔️"

.PHONY:		all bonus clean fclean re fast


