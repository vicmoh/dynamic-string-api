/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"
#include "Tokenizer.h"
#include "ArrayMap.h"
#include "LinkedList.h"

typedef struct{
    long double x;
    long double y;
}Point;

CLASS(Point, (long double x, long double y),
    CONSTRUCTOR(
        this->x = x;
        this->y = y;
    ),//end constructor

    Point* point_clone(Point* pointToBeClone){
        Point* new = new_Point(pointToBeClone->x, pointToBeClone->y);
        return new;
    }//end func

    void point_free(void* this){
        if(this == NULL){
            return;
        }//end if
        free(this);
    }//end func

    void point_multiply(Point* this, int numToMultiply){
        this->x *= numToMultiply;
        this->y *= numToMultiply;
    }//end func
);//end 

static jmp_buf s_jumpBuffer;

void Test() {
  // Rough equivalent of `throw`
  longjmp(s_jumpBuffer, 42);
}


void Example() { 
  if (setjmp(s_jumpBuffer)) {
    // The longjmp was executed and returned control here
    printf("Exception happened here\n");
  } else {
    // Normal code execution starts here
    Test();
  }
}

int main(){

    // garbage collector
    MEM_START;
    String MEM(asdfafse, 123);
    String MEM(someString, 123);
    String MEM(secondString, 123);
    String MEM(someDude, 123);
    String MEM(stringTest, 123);
    
    stringTest = someDude;
    asdfafse = someString;
    asdfafse = secondString;
    strcpy(someDude, "hello");

    MEM_DELETE;
    printf("1 2 = %p %p\n", someString, asdfafse);


    // testing classes
    Point* point = new_Point(10, 10);
    print("before = ", _(point->x), " ", _(point->y));
    point_multiply(point, 5);
    print("after = ", _(point->x), " ", _(point->y));
    point_free(point);


    //c
    Array* listOfCars = new_Array(string_free);
    listOfCars->add(listOfCars, $("Lambo"));
    listOfCars->add(listOfCars, $("Honda"));

    // java
    // Array listOfCars = new Array();
    // listOfCars.add("Lambo");
    // listOfCars.add("Honda");

    print("car is ", listOfCars->getIndexOf(listOfCars, 1));
    listOfCars->destroy(listOfCars);

    /**
     * this is your playground, you can test the API below
     * to run the test type "make testing" on terminal program directory
     */

    //******************************************* testing string tag

    String test = $("Hello world!");
    print("print1: ", test);

    String name = $("Vic");
    String sayHello = NULL;

    sayHello = $("Hello my name is ", name, ", how is it going?");
    print("print2: ", sayHello);

    const int age = 8;
    String sayYourCodeYears = $("I have been coding for ", _(age), " years.");
    print("print", _(3) , ": ", sayYourCodeYears); 

    int num1 = 2;
    int num2 = 2;
    String addition = $(_(num1), " plus ", _(num2), " is ", _(num1+num2));
    print("print4: ", addition, " minus 1 that's 3 quick math.");

    const double pi = 3.14159;
    String sayPiInDecimal = $("What is the Pi number? ", _dec(pi, 2), " is the number, duh!");
    print("print", _dec(5, 0), ": ", sayPiInDecimal);

    String salute = $("hello");
    print("the salute value is ", salute);
    $$(salute) = $("cya");
    print("the salute value is ", salute);
    $$(salute) = $("okay");
    $$(salute) = $("dude");
    print("the salute value is ", salute);
    free(salute);

    // free
    free(test);
    free(name);
    free(addition);
    free(sayHello);
    free(sayYourCodeYears);
    free(sayPiInDecimal);

    //**************************************************token test

    String toBeSplit = $("This string is going to be split into array of string");
    Token* token = new_Token(toBeSplit, " ");
    for(int x=0; x<token->length; x++){
        print("token[", _(x), "]: ", token->list[x]);
    }//end for

    String combineString = token->combine(token, 3, 6);
    print("outputing 3 and 6 = (", combineString, ")");

    int indexSearch = token->search(token, "going", true);
    print("the index token is ", _(indexSearch));

    indexSearch = token->search(token, "string", false);
    print("found ", _(indexSearch), " with the name string");


    //***********************************************************array test

    Array* listOfString = new_Array(NULL);

    for_in(x, token){
        listOfString->add(listOfString, token->list[x]);
    }//end if

    for_in(x, listOfString){
        print("Array[", _(x), "]: ", listOfString->getIndexOf(listOfString, x));
    }//end if

    listOfString->removeIndexOf(listOfString, 3);
    print("List of new array after delete");
    for_in(x, listOfString){
        print("Array[", _(x), "]: ", listOfString->getIndexOf(listOfString, x));
    }//end for

    //**********************************************************map test

    Map* map = new_Map(11, string_free);

    map->add(map, "one", $("hunny"));
    map->add(map, "two", $("boo boo"));
    map->add(map, "three", $("yee"));
    map->add(map, "four", $("okay"));
    map->add(map, "five", $("dude"));
    map->add(map, "six", $("sup"));
    map->add(map, "seven", $("keep"));
    map->add(map, "eight", $("goin"));
    map->add(map, "nine", $("please"));
    map->add(map, "ten", $("stop")); 
    map->add(map, "eleven", $("wow"));
    map->add(map, "twelve", $("nah"));
    map->add(map, "thirteen", $("im"));
    map->add(map, "fourteen", $("done"));
    
    print("one = ", map->get(map, "one"));
    print("two = ", map->get(map, "two"));
    print("three = ", map->get(map, "three"));
    print("four = ", map->get(map, "four"));
    print("five = ", map->get(map, "five"));
    print("six = ", map->get(map, "six"));
    print("seven = ", map->get(map, "seven"));
    print("eight = ", map->get(map, "eight"));
    print("nine = ", map->get(map, "nine"));
    print("ten = ", map->get(map, "ten"));
    print("nine = ", map->get(map, "eleven"));
    print("ten = ", map->get(map, "twelve"));
    print("thirteen = ", map->get(map, "thirteen"));
    print("fourteen = ", map->get(map, "fourteen"));

    map->destroy(map);
    free(combineString);
    free(toBeSplit);
    token->destroy(token);
    listOfString->destroy(listOfString);

    //testing class

}//end main