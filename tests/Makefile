DIR		= clang -C../tests



testaccess:
	clang testaccess.c ../libft.a -I../ && ./a.out

testexecve:
	clang testexecve.c ../libft.a -I../ && ./a.out

testpipe:
	clang testpipe.c ../libft.a -I../
	echo "hello" > file2
	./a.out file1 file2 && cat file2

testping:
	clang testping.c ../libft.a -I../ && ./a.out
