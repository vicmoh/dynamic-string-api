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


    /******************** ARRAY ********************/
    // API also includes data structure such as map, array, and linked list:
    Array* strings = new_Array(string_free);
    array_addMultiple(strings, 
        $("first string"),
        $("second string"),
        $("third string"),
        $("fourth string")
    );
    // you can also use for in loop for map, array or linked list
    print("\n---------- Array Output ----------");
    for_in(x, strings){
        print("Index[",_(x),"]: ", array_get(strings, x));   
    }//end for


    /******************** MAP ********************/
    Map* cars = new_Map(string_free);
    String ferrariKey = $("Ferrari");
    String hondaKey = $("Honda");
    // Adding to the map
    map_add(cars, ferrariKey, $("Price of ", ferrariKey,": $300,000"));
    map_add(cars, hondaKey, $("Price of ", hondaKey, ": $20,000"));
    // Get the data by passing the key
    print("\n---------- Map Ouput ----------");
    print(map_get(cars, "Ferrari"));
    print(map_get(cars, "Honda"));


    /******************** TOKENIZER ********************/
    // You can also split string through the token object
    // which split the token into an array of tokens similar to Java:
    String toBeSplit = $("This string is going to be split into array of string");
    Token* token = new_Token(toBeSplit, " ");
    print("\n---------- Token Ouput ----------");
    for_in(x, token){
        print("token[",_(x),"]: ", token_getTokenAt(token, x));
    }//end for


    delete(toBeSplit, ferrariKey, hondaKey);
    map_free(cars);
    token_free(token);
    array_free(strings);
}//end main
