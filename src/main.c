/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"
#include "Tokenizer.h"
#include "ArrayMap.h"
#include "LinkedList.h"

int main(){
    /**
     * Run your code here.
     * To run the program type "make" or "make valgrind" on program directory and it will compile and run.
     * Place any of your .c in (src) folder and .h in (include).
     * No need to change the makefile.
     * Any files you placed in (scr), (include), (lib) will automatically compile and run, just type "make".
     * Here are some example API codes below.
     **/

    // Simply, any tag inside '$( )' is a string.
    // Higher level languages uses '+' symbol to assign multiple strings together.
    // In comparison, you can assign similar way using ',' to represent different strings inside the string tag.
    // Similar to other language, the function 'print( )' is also available using the string tag format which ouput to console.

    // To declare a string:
    String test = $("Hello world!");
    print("print1: ", test);

    String name = $("Vic");
    String sayHello = NULL;

    // You can also assign with other string. 
    // As long as it is in the string tag it will return a dynamicly allocated combined string:
    sayHello = $("Hello my name is ", name, ", how is it going?");
    print("print2: ", sayHello);

    // Number variables such as int or double in string tag '$( )' must use '\_( )' or it will not compile.
    // You can also use constant numbers instead of variables such as '\_(3)':
    const int age = 8;
    String sayYourCodeYears = $("I have been coding for ", _(age), " years.");
    print("print", _(3) , ": ", sayYourCodeYears); 

    // Another example:
    int num1 = 2;
    int num2 = 2;
    String addition = $(_(num1), " plus ", _(num2), " is ", _(num1+num2));
    print("print4: ", addition, " minus 1 that's 3 quick math.");

    // Here's another example to print with decimal places on numbers.
    // The first argument in '_dec( )' is the value, and the second is the number of decimal places to show:
    const double pi = 3.14159;
    String sayPiInDecimal = $("What is the Pi number? ", _dec(pi, 2), " is the number, duh!");
    print("print", _dec(5, 0), ": ", sayPiInDecimal);

    // String tag returns a dynamic allocated string.
    // Hence, you have to free each dynamic string manually:
    delete(test, name, addition, sayHello, sayYourCodeYears, sayPiInDecimal);

    // You can also split string through the token object
    // which split the token into an array of tokens similar to Java:
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
    token_free(token);
}//end main
