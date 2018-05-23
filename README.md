# Dynamic String API for C

A dynamic string API to make string coding much easier in C similar to other modern languages.

## Installation of API

### 1. Download

```Bash
git clone https://github.com/vicmoh/DynamicStringAPI
```

### 2. Run

To compile and run the program type `make` or `make valgrind` on terminal program directory.
Place any of your `.c` files in `src` folder and `.h` in `include`.
No need to change the `makefile`.
Any files you placed in `scr`, `include`, `lib` will automatically compile and run the program when `make` is invoked.

```bash
make
```

### Directory Structure

Any C file should be placed under the `src` folder.
There is already `main.c` where you can start your project.

```Bash
src/main.c
```

Any shared or static libraries goes under the `lib` folder.

```Bash
lib/DynamicString.a
```

Your header .h files must be inside the `include` folder.

```Bash
include/DynamicString.h
include/Tokenizer.h
```

The bin folder is where the executable files goes to,
by default, `runProgram` will be your executable when `make` is invoked on the terminal.

```Bash
bin/runProgam
```

## How to Use the API

### String Usage

Simply, any tag inside `$( )` is a string.
Higher level languages uses `+` symbol to assign multiple strings together.
In comparison, you can assign similar way using `,` to represent different strings inside the string tag.
Similar to other languages, the function `print( )` is also available using the string tag format which ouput to console.

To declare a string:

```javascript
String test = $("Hello world!");
print("print1: ", test);

/************ output ************
print1: Hello world!
*********************************/
```

You can also assign string with other string. As long as it is in the string tag it will return a dynamicly allocated combined string:

```javascript
String name = $("Vic");
String sayHello = NULL;
String toBeAssigned = NULL;

sayHello = $("Hello my name is ", name, ", how is it going?");
toBeAssigned = $(sayHello);
print("print2: ", toBeAssigned);

/************ output ************
print2: Hello my name is Vic, how is it going?
*********************************/
```
### Number in String

Number variables such as int or double in string tag `$( )` must use `_( )` or it will not compile.
You can also use constant numbers inside instead of variables such as `_(3)`:

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
The first argument in `_dec( )` is the value, and the second is the number of decimal places to show:

```javascript
double pi = 3.14159;
String sayPiInDecimal = $("What is the Pi number? ", _dec(pi, 2), " is the number, duh!");
print("print", _dec(5, 0), ": ", sayPiInDecimal);

/************ output ************
print5: What is the Pi number? 3.14 is the number, duh!
*********************************/
```

### Memory Management

Previously this is how we use to code string in C. We had to use an array of chars:

```javascript
// Previously when we use string in C
char sayYourName[30];
char name[30]; 
strcpy(name, "Jeff");
strcpy(sayYourName, "My name is ");
strcat(sayYouName, name);
strcat(sayYouNam, ".");

/************ output ************
My name is Jeff.
*********************************/
```

The code above is how we manipulate char array in C, problem with this is that the size is constant and it could not hold string longer than `30`. So what if it happens to be a longer string? 

Another way to fix the problem is to create a dynamic char array by mallocing and then reallocing to a bigger size when we need to hold more char. So, we have to keep track of the size and it can be difficult to manage.

```javascript
// Dynamically char size previously how we use to code
char* sayYourName = malloc(sizeof(char*)*30);
char* name = malloc(sizeof(char*)*30);
strcpy(name, "Jeff");
strcpy(sayYourName, "My name is ");
strcat(sayYouName, name);
strcat(sayYouNam, ".");

// And when we need more memory we can just realloc the size
char* sayYouName = realloc(sayYourName, sizeof(char*)*50)

/************ output ************
My name is Jeff.
*********************************/
```

The string tag `$( )` is a simpler form of dynamic chars in C which will adjust accordingly based on the string size. As a result, there is no need to keep track of the memory size of the char array, it will adjust dynamically based on the string size for you. Hence, making dynamic string simpler to code in C similar to other modern languages!

```javascript
// The new way of manipulatinge string in C
String name = $("Jeff");
String sayYouName = $("My name is ", name, ".");

// In comparison to JavaScript
var name = "Jeff";
var sayYouName = "My name is " + name + ".";

/************ output ************
My name is Jeff.
*********************************/
```

However, since string tag returns a dynamic allocated string,
every new string that has been created does not have an auto garbage collector *(will be added on future updates)*.
Some operating system manages out the memory when its not freed, but it's better to do it manually, so don't forget to free your string!

```javascript
free(test);
free(name);
free(multiply);
free(sayHello);
free(toBeAssigned);
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