CC = gcc
CFLAGS = -Wall -g -Iinclude -std=c11
BIN = bin/
SRC = lib/src/

# to run you program

program: createProgram runProgram

createProgram:
	$(CC) $(CFLAGS) src/*.c lib/*.a -o bin/runProgram -lm

runProgram:
	./bin/runProgram

# shared library

lib: createSharedLib createStaticLibrary cleanObject

createSharedLib: $(BIN)DynamicString.o $(BIN)ArrayMap.o $(BIN)Tokenizer.o $(BIN)LinkedList.o
	$(CC) -shared -o lib/DynamicStringAPI.so $(BIN)DynamicString.o $(BIN)ArrayMap.o $(BIN)Tokenizer.o $(BIN)LinkedList.o

$(BIN)DynamicString.o: $(SRC)DynamicString.c
	$(CC) $(CFLAGS) -fpic -Iinclude -c $(SRC)DynamicString.c -o $(BIN)DynamicString.o

$(BIN)ArrayMap.o: $(SRC)ArrayMap.c
	$(CC) $(CFLAGS) -fpic -Iinclude -c $(SRC)ArrayMap.c -o $(BIN)ArrayMap.o

$(BIN)Tokenizer.o: $(SRC)Tokenizer.c
	$(CC) $(CFLAGS) -fpic -Iinclude -c $(SRC)Tokenizer.c -o $(BIN)Tokenizer.o

$(BIN)LinkedList.o: $(SRC)LinkedList.c
	$(CC) $(CFLAGS) -fpic -Iinclude -c $(SRC)LinkedList.c -o $(BIN)LinkedList.o

# test command

testing: createStaticLibrary createTest runTest

createTest:
	$(CC) $(CFLAGS) test/test.c lib/*.a -o bin/runTest -lm

runTest:
	valgrind --leak-check=full ./bin/runTest

# creating a createStaticLibrary

createStaticLibrary: DynamicString.o Tokenizer.o ArrayMap.o LinkedList.o libraryCreate cleanObject

createObject: DynamicString.o Tokenizer.o ArrayMap.o LinkedList.o

DynamicString.o: lib/src/DynamicString.c
	$(CC) $(CFLAGS) -fpic -c lib/src/DynamicString.c -o bin/DynamicString.o

Tokenizer.o: lib/src/Tokenizer.c
	$(CC) $(CFLAGS) -fpic -c lib/src/Tokenizer.c -o bin/Tokenizer.o

ArrayMap.o: lib/src/ArrayMap.c
	$(CC) $(CFLAGS) -fpic -c lib/src/ArrayMap.c -o bin/ArrayMap.o

LinkedList.o: lib/src/LinkedList.c
	$(CC) $(CFLAGS) -fpic -c lib/src/LinkedList.c -o bin/LinkedList.o

libraryCreate:
	ar rc lib/DynamicStringAPI.a bin/DynamicString.o bin/Tokenizer.o bin/ArrayMap.o bin/LinkedList.o

#ranlib DynamicStringAPI.a
# other command

valgrind: createProgram runValgrind

runValgrind:
	valgrind --leak-check=full ./bin/runProgram

cleanLibrary:
	rm lib/*.a

cleanObject:
	rm bin/*.o

clean:
	rm bin/*