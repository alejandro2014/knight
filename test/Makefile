knight_test: main_test.o write_console.o
	gcc main_test.o write_console.o -o knight_test

main_test.o: main_test.c
	gcc -c main_test.c -o main_test.o

write_console.o: ../src/console/write_console.c
	gcc -c ../src/console/write_console.c -o write_console.o
