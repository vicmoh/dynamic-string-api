CC = gcc
CFLAGS = -Wall -g -Iinclude -std=c11

# to run you program

program: createProgram runProgram

createProgram:
	$(CC) $(CFLAGS) src/*.c lib/*.a -o bin/runProgram -lm

runProgram:
	./bin/runProgram

# test command

testing: library createTest runTest

createTest:
	$(CC) $(CFLAGS) test/test.c lib/*.a -o bin/runTest -lm

runTest:
	valgrind --leak-check=full ./bin/runTest

# creating a library

library: DynamicString.o Tokenizer.o ArrayMap.o libraryCreate cleanObject

DynamicString.o:
	$(CC) $(CFLAGS) -c lib/src/DynamicString.c -o bin/DynamicString.o

Tokenizer.o:
	$(CC) $(CFLAGS) -c lib/src/Tokenizer.c -o bin/Tokenizer.o

ArrayMap.o:
	$(CC) $(CFLAGS) -c lib/src/ArrayMap.c -o bin/ArrayMap.o

libraryCreate:
	ar rc lib/DynamicStringAPI.a bin/DynamicString.o bin/Tokenizer.o bin/ArrayMap.o

#ranlib DynamicStringAPI.a
# other command

valgrind: program runValgrind

runValgrind:
	valgrind --leak-check=full ./bin/runProgram

cleanLibrary:
	rm lib/*.a

cleanObject:
	rm bin/*.o

clean:
	rm bin/*