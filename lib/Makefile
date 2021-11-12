NAME	=	libft.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

OBJS_DIR =	.obj

HEADER	= libft.h

SOURCES	= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
          ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strrchr.c \
          ft_strnstr.c ft_strncmp.c ft_strchr.c ft_strlcat.c\
          ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
          ft_isprint.c ft_toupper.c ft_tolower.c \
          ft_calloc.c ft_strdup.c \
          ft_substr.c ft_strjoin.c ft_strtrim.c \
          ft_split.c ft_itoa.c ft_strmapi.c \
          ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJECTS	= $(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SOURCES)))

$(OBJS_DIR)/%.o:	%.c ${HEADER}
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $?
	@ranlib $(NAME)

all: $(NAME)

clean:
	@-rm -f $(OBJECTS)
	@-rm -rf $(OBJS_DIR)
	@printf "$(UNDER_LINE)$(BOLD)$(NAME):$(NO_COLOR) $(LIGHT_RED)Object files deleted$(NO_COLOR)\n"

fclean: clean
	@-rm -rf $(NAME)
	@printf "$(UNDER_LINE)$(BOLD)$(NAME):$(NO_COLOR) $(LIGHT_RED)All files deleted$(NO_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re

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