DIR		= clang -C../tests



testaccess:
	clang ./tests/testaccess.c libft.a -I. && ./a.out

testexecve:
	clang ./tests/testexecve.c libft.a -I. && ./a.out

# testpipe:
# 	clang ./tests/testpipe.c libft.a -I.
# 	-C ./tests ../a.out file1 file2

testping:
	clang ./tests/testping.c libft.a -I. && ./a.out

