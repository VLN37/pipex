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

SRC		= $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJ		= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

VPATH	= src

all:	$(OBJDIR) $(NAME)

complete: $(OBJDIR) $(NAME) $(BONUSNAME)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKS)

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

$(OBJDIR):
	mkdir -p obj
