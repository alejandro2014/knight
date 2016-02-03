EXE=knight_test
FILE_TEST_DIR=../src/console
FILE_TEST=write_console

${EXE}: main_test.o ${FILE_TEST}.o
	gcc main_test.o ${FILE_TEST}.o -o ${EXE}

main_test.o: main_test.c
	gcc -c main_test.c -o main_test.o

${FILE_TEST}.o: ${FILE_TEST_DIR}/${FILE_TEST}.c
	gcc -c ${FILE_TEST_DIR}/${FILE_TEST}.c -o ${FILE_TEST}.o

clean:
	rm -f ${FILE_TEST}.o main_test.o ${EXE}
