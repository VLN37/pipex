DIR		= clang -C../tests

pipex:
	clang pipex.c libft.a -fsanitize=address -g3
	./a.out file1 "grep reprehen" "tr ' ' '\n'" file2

debug:
	clang pipex.c libft.a -D DEBUG=3
	./a.out file1 "grep reprehen" "tr ' ' '\n'" file2

runf:
	clang pipex.c libft.a -fsanitize=address -g3
	./a.out file1 "grep reprehen" "tr ' ' '\n'" file2

runv:
	clang pipex.c libft.a
	valgrind ./a.out file1 "grep reprehen" "tr ' ' '\n'" file2
