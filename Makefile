NAME		=	minishell

CC			=	gcc

OBJS_DIR	=	.obj

HEADER =  libshell.h parser/parser.h

CFLAGS	= -Wall -Wextra -Werror

SRCS	=	main.c parser/parser.c parser/split.c parser/quoters.c parser/redirects.c parser/dollar.c \
			parser/preparsing.c parser/one_command.c parser/num_of_pipes.c cmd/build_in.c cmd/build_in_utils.c \
			cmd/export.c cmd/launch_exe.c utils.c utils_signals.c cmd/execuate.c parser/ft_free_close.c \
			parser/ft_pipe.c parser/last_command.c parser/redirect_readline.c parser/redirect_utils.c \
			parser/redirect_utils_2.c parser/parse_one_command.c cmd/cd.c cmd/export_pt2.c utils2.c

OBJS	= $(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))


$(OBJS_DIR)/%.o:	%.c ${HEADER}
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@test -d .obj/parser || mkdir .obj/parser
					@test -d .obj/cmd || mkdir .obj/cmd
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

all:	$(NAME)

$(NAME): ${OBJS}
		@printf "Compilation of libft...\r"
		@$(MAKE) -C lib -s >/dev/null
		@printf "$(GREEN)$(BOLD)libft compiled          $(NO_COLOR)\n"
		@ar rc libhell.a $?
		@ranlib libhell.a
		@gcc -L. -lhell -Llib -lft -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline -o ${NAME}
		@printf "$(GREEN)$(BOLD)Compilation completed$(NO_COLOR)\n"

clean:
		@rm -f ${OBJS} libhell.a
		@-rm -rf $(OBJS_DIR)
		@$(MAKE) clean -sC lib

fclean:	clean
		@rm -f ${NAME}
		@$(MAKE) fclean -C lib
		@printf "$(UNDER_LINE)$(BOLD)$(NAME):$(NO_COLOR) $(CYAN)All files deleted$(NO_COLOR)\n"

re:		fclean all

run:	all
		./$(NAME)

.PHONY:	all clean fclean re run

################
##   COLORS   ##
################

BOLD	 	= \033[1m
NO_COLOR 	= \033[0m
UNDER_LINE	= \033[4m

BLACK	 	= \033[0;30m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
BROWN 	 	= \033[0;33m
BLUE 		= \033[0;34m
PURPLE 	 	= \033[0;35m
CYAN 	 	= \033[0;36m
LIGHT_GRAY	= \033[0;37m

DARK_GRAY	= \033[1;30m
LIGHT_RED	= \033[1;31m
LIGHT_GREEN	= \033[1;32m
YELLOW 		= \033[1;33m
LIGHT_BLUE	= \033[1;34m
LIGHT_PURPLE= \033[1;35m
LIGHT_CYAN	= \033[1;36m
WHITE 		= \033[1;37m
