
hash_table.o : hash_table.c hash_table.h
	gcc -c hash_table.c

file_diff : file_diff.c hash_table.o hash_table.h
	gcc -o file_diff file_diff.c hash_table.o
