NAME 	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

SRC_PATH = ./src/

OBJ_PATH = obj/

SRC		= readline.c \
			parser.c \
			lexer/lexer.c \
			lexer/lexer_utils.c \

SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
INCS		= -I ./inc/

LIBDIR = ./libft/
LIBFT = ./libft/libft.a

RM 			:= rm -rf
MAKEFLAGS	+= --no-print-directory

all: $(OBJ_PATH) $(LIBFT) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
		$(CC) $(CFLAGS) -I$(LIBDIR) -c $< -o $@ $(INCS)

$(OBJ_PATH):
		mkdir -p obj 
		mkdir -p obj/lexer

$(NAME): $(OBJ_PATH) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
		make -C $(LIBDIR)

clean:
	$(RM) obj

fclean: clean
		$(RM) $(NAME) 

re: 
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re bonus
