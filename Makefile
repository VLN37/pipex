LIBFTDIR= ./libft
LIBFT	= $(LIBFTDIR)/libft.a

MKLIBFT	= make -C ./libft
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3
HEADER	= pipex.h
BONUSHEADER	= pipex_bonus.h
BONUSNAME	= pipex_bonus
NAME	= pipex
RM		= rm -f
INCLUDES= -I./libft -I./
LINKS	= -I./libft -I./ -L./libft -lft

SRCDIR	= src
BONUSDIR= srcbonus
OBJDIR	= obj
SRCFILES		= pipex.c \
				  pipex_parse.c \
				  pipex_validation.c \
				  pipex_utils.c \
				  pipex_exec.c \

BONUSSRCFILES	= pipex_bonus.c \
				  pipex_parse_bonus.c \
				  pipex_utils_bonus.c \
				  pipex_validation_bonus.c \
				  pipex_exec_bonus.c \

SRC		= $(addprefix $(SRCDIR)/, $(SRCFILES))
BONUSSRC= $(addprefix $(BONUSDIR)/, $(BONUSSRCFILES))
OBJ		= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BONUSOBJ= $(BONUSSRC:$(BONUSDIR)/%.c=$(OBJDIR)/%.o)

VPATH	= src srcbonus

all:	$(OBJDIR) $(NAME)

bonus:	$(OBJDIR) $(BONUSNAME)

complete: $(OBJDIR) $(NAME) $(BONUSNAME)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKS)

$(BONUSNAME): $(LIBFT) $(BONUSOBJ) $(BONUSHEADER)
	$(CC) $(CFLAGS) $(BONUSOBJ) -o $(BONUSNAME) $(LINKS)

$(OBJDIR)/%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT):
	make -C ./libft

clean:
	make -C ./libft clean
	$(RM) $(OBJ)
	rm -rf obj

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME) $(BONUSNAME)

re:		fclean all

run: $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
	./pipex file1 "tr a ' '" "tr ' ' x" file2

runf:
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME) -fsanitize=address -g3
	./pipex file1 "tr a ' '" "tr ' ' 'x'" file2

runv:
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
	valgrind ./pipex file1 "tr a ' '" "tr ' ' 'x'" file2

$(OBJDIR):
	mkdir -p obj
