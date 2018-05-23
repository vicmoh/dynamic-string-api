# Dynamic String API for C

This is dynamic string API to make string coding much easier in C.

## Installation of API

### 1. Downlaod

```Bash
git clone https://github.com/vicmoh/DynamicStringAPI
```

### 2. Run

To compile and run the program type 'make' or 'make valgrind' on terminal program directory.
Place any of your .c files in 'src' folder and .h in 'include'.
No need to change the 'makefile'.
Any files you placed in 'scr', 'include', 'lib' will automatically compile and run the program when 'make' is invoked.

```bash
make
```

### Directory Structure

Any C file should be placed under the 'src' folder.
There is already main.c where you can start your project.

```Bash
src/main.c
```

Any shared or static libraries goes under the 'lib' folder.

```Bash
lib/DynamicString.a
```

Your header .h files must be inside the 'include' folder.

```Bash
include/DynamicString.h
```

The bin folder is where the executable files goes to,
by default, 'runProgram' will be your executable when 'make' is invoked.

```Bash
bin/runProgam
```

## How to Use the API

### String usage

Simply, any tag inside '$( )' is a string.
Higher level languages uses '+' symbol to assign multiple strings together.
In comparison, you can assign similar way using ',' to represent different strings inside the string tag.
Similar to other language, the function 'print( )' is also available using the string tag format which ouput to console.

To declare a string:

```javascript
String test = $("Hello world!");
print("print1: ", test);

/************ output ************
print1: Hello world!
*********************************/
```

You can also assign with other string. As long as it is in the string tag it will return a dynamicly allocated combined string:
```javascript
String name = $("Vic");
String sayHello = NULL;

sayHello = $("Hello my name is ", name, ", how is it going?");
print("print2: ", sayHello);

/************ output ************
print2: Hello my name is Vic, how is it going?
*********************************/
```
### Numbers in string

Number variables such as int or double in string tag '$( )' must use '\_( )' or it will not compile.
You can also use constant numbers instead of variables such as '\_(3)':
```javascript
int age = 8;
String sayYourCodeYears = $("I have been coding for ", _(age), " years.");
print("print", _(3) , ": ", sayYourCodeYears); 

/************ output ************
print3: I have been coding for 8 years.
*********************************/
```

Another example:
```javascript
int num1 = 2;
int num2 = 2;
String addition = $(_(num1), " plus by ", _(num2), " is ", _(num1+num2));
print("print4: ", addition, " minus 1 that's 3 quick math.");

/************ output ************
print4: 2 plus 2 is 4 minus 1 that's 3 quick math.
*********************************/
```

Here's another example to print with decimal places on numbers.
The first argument in '\_dec( )' is the value, and the second is the number of decimal places to show:
```javascript
double pi = 3.14159;
String sayPiInDecimal = $("What is the Pi number? ", _dec(pi, 2), " is the number, duh!");
print("print", _dec(5, 0), ": ", sayPiInDecimal);

/************ output ************
print5: What is the Pi number? 3.14 is the number, duh!
*********************************/
```

### Memory management

String tag returns a dynamic allocated string,
Every new string does not have an auto garbage collector _(will be added on future update).
Hence, you have to free each dynamic string manually:
```javascript
free(test);
free(name);
free(multiply);
free(sayHello);
free(sayYourCodeYears);
free(sayPiInDecimal);
```

### Tokenizer

You can also split string through the token object
which split the token into an array of tokens similar to Java:
```javascript
String toBeSplit = $("This string is going to be split into array of string");
Token* token = split(toBeSplit, " ");
for(int x=0; x<token->length; x++){
    print("token[", _(x), "]: ", token->list[x]);
}//end for

/************ output ************
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
token[10]: string
*********************************/

free(toBeSplit);
Token_freeToken(token);
```