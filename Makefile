DIR		= clang -C../tests
CC		= clang
CFLAGS	= -Wall -Wextra -Werror
NAME	= pipex
RM		= rm -f
OBJ		= $(SRCS:.c=.o)
SRCS	= pipex.c \
		  pipex_parse.c \

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft.a -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:		fclean all

debug:
	$(CC) $(CFLAGS) $(SRCS) libft.a -o $(NAME) -D DEBUG=1
	./pipex file1 "tr a ' '" "tr ' ' b" file2

run:
	$(CC) $(CFLAGS) $(SRCS) libft.a -o $(NAME)
	./pipex file1 "tr a ' '" "tr ' ' 'x'" file2
#	./a.out file1 "grep reprehen" "tr ' ' '\n'" file2

runf:
	$(CC) $(CFLAGS) $(SRCS) libft.a -o $(NAME) -fsanitize=address -g3
	./pipex file1 "tr a ' '" "tr ' ' 'x'" file2

runv:
	$(CC) $(CFLAGS) $(SRCS) libft.a -o $(NAME)
	valgrind ./pipex file1 "tr a ' '" "tr ' ' 'x'" file2
