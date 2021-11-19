CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g3
HEADER	= pipex.h
BONUSHEADER	= pipex_bonus.h
BONUSNAME	= pipexbonus
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


all:	mkdir $(NAME)

bonus:	mkdir $(BONUSNAME)

complete: mkdir $(NAME) $(BONUSNAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKS)

$(BONUSNAME): $(BONUSOBJ) $(BONUSHEADER)
	make -C ./libft
	$(CC) $(CFLAGS) $(BONUSOBJ) -o $(BONUSNAME) $(LINKS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR)/%.o:	$(BONUSDIR)/%.c $(BONUSHEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	make -C ./libft clean
	$(RM) $(OBJ)
	rm -rf obj

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME) $(BONUSNAME)

re:		fclean all

debug:
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME) -D DEBUG=1
	./pipex file1 "tr a ' '" "tr ' ' b" file2

debug2:
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME) -D DEBUG=1
	./pipexbonus here_doc OUT "tr a ' '" "tr ' ' b" file2

run: $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
	./pipex file1 "tr a ' '" "tr ' ' x" file2
#	./a.out file1 "grep reprehen" "tr ' ' '\n'" file2

runf:
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME) -fsanitize=address -g3
	./pipex file1 "tr a ' '" "tr ' ' 'x'" file2

runv:
	$(CC) $(CFLAGS) $(SRCS) ./libft/libft.a -o $(NAME)
	valgrind ./pipex file1 "tr a ' '" "tr ' ' 'x'" file2

mkdir:
	mkdir -p obj
