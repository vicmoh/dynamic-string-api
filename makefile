CC = gcc
CFLAGS = -Wall -g -Iinclude -std=c11

# to run you program

program: createProgram runProgram

createProgram:
	$(CC) $(CFLAGS) src/*.c lib/*.a -o bin/runProgram

runProgram:
	./bin/runProgram

# test command

testing: createTest runTest

createTest:
	$(CC) $(CFLAGS) test/test.c lib/*.a -o bin/runTest

runTest:
	./bin/runTest

# creating a library

library: DynamicString.o Tokenizer.o libraryCreate cleanObject

DynamicString.o:
	$(CC) $(CFLAGS) -c lib/src/DynamicString.c -o bin/DynamicString.o

Tokenizer.o:
	$(CC) $(CFLAGS) -c lib/src/Tokenizer.c -o bin/Tokenizer.o

libraryCreate:
	ar rc lib/DynamicStringAPI.a bin/DynamicString.o bin/Tokenizer.o
	
#ranlib DynamicStringAPI.a
# other command

valgrind: program runValgrind

runValgrind:
	valgrind ./bin/runProgram

cleanObject:
	rm bin/*.o

clean:
	rm bin/*