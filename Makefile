default:
	gcc -o date date.c
	gcc -o cat cat.c
	gcc -o ls ls.c
	gcc -o mkdir mkdir.c
	gcc -o rm rm.c
	gcc main.c -lreadline
	./a.out