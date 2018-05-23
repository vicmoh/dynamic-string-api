# Dynamic String API for C

This is an API to make coding much easier in C.
Since, string is an array or char, the API uses preprocessor of char*  which act as String.
Hence you can pass string around through char* parameter.

## Installation of API

### 1. Downlaod

```Bash
git clone https://github.com/vicmoh/DynamicStringAPI
```

### 2. run

To run the program type "make" or "make valgrind" on program directory and it will compile and run.
Place any of your .c in "src" folder and .h in "include".
No need to change the makefile.
Any files you placed in "scr", "include", "lib" will automatically compile and run, just type "make".
Here are some example API codes below.

### Directory Structure

Any C file should be placed under the "src" folder.
There is already main.c where you can start you project.

```Bash
src/main.c
```

Any shared or static libraries goes under the "lib" folder.

```Bash
lib/DynamicString.a
```

Your header .h files must be inside the "include" folder.

```Bash
include/index.js
```

The bin folder is where the executable goes to,
by default when "make", it will compile and create "runProgram",
which will then run.

```Bash
bin/runProgam
```

## How to Use the API

### String usage

Simply, any tag inside "$( )" is a string, 
you can assign multiple string with comma "," inside to represent different string.
Print() also works the same way as many other modern language which outputs to console.
To declare a string simply:

```javascript
String test = $("Hello world!");
print("print1: ", test);

String name = $("Vic");
String sayHello = NULL;
```

You can assign with other string and print using the same format:
```javascript
sayHello = $("Hello my name is ", name, ", how is it going?");
print("print2: ", sayHello);
```
### Numbers in string

Using numbers in string
number variable in string "$( )" must use "_(age)" or it will not compile:
```javascript
int age = 8;
String sayYourCodeYears = $("I have been coding for ", _(age), " years.");
print("print", _(3) , ": ", sayYourCodeYears); 
```

Another example:
```javascript
int num1 = 2;
int num2 = 4;
String multiply = $(_(num1), " mulitply by ", _(num2), " is ", _(num1*num2));
print("print4: ", multiply);
```

Here's another example to print with decimals with numbers:
```javascript
double pi = 3.14159;
String sayPiInDecimal = $("What is the Pi number? ", _dec(pi, 2), " is the number, duh!");
print("print", _dec(5, 0), ": ", sayPiInDecimal);

// dynamic string return dynamic allocated memory
// dynamic string does not have an auto garbage collector (will be added on future updates)
// you have to free each dynamic string manually 
free(test);
free(name);
free(multiply);
free(sayHello);
free(sayYourCodeYears);
free(sayPiInDecimal);
```

You can you also split string through the token object
which split the token into an array of tokens similar to Java:
```javascript
String toBeSplit = $("This string is going to be split into array of string");
Token* token = split(toBeSplit, " ");
for(int x=0; x<token->length; x++){
    print("token[", _(x), "]: ", token->list[x]);
}//end for

/* the output will be:
token[0]: This
token[1]: string
token[2]: is
token[3]: going
token[4]: to
token[5]: be
token[6]: split
token[7]: into
token[8]: array
token[9]: of
token[10]: string*/

free(toBeSplit);
Token_freeToken(token);
```