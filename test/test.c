/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"
#include "Tokenizer.h"
#include "ArrayMap.h"
#include "LinkedList.h"

CLASS(Point, (long double x, long double y),
    // To declare an instance variable
    // you must add "," comma at the end
    long double x;
    long double y;
    String toString,

    // Use "this" to access the instance
    // variable members in Point
    // don't forget "," comma at the end
    CONSTRUCTOR(
        this->x = x;
        this->y = y;
        this->toString = $("cordinate: ", _(this->x), ", ", _(this->y));
    ),//end constructor

    // function to free object
    void point_free(void* obj){
        Point* this = obj;
        if(this == NULL){
            return;
        }//end if
        delete(this->toString, this);
    }//end func

    // toString function
    void point_toString(Point* this){
        free(this->toString);
        this->toString = $("cordinate: ", _(this->x), ", ", _(this->y));
    }//end func

    // cloning function
    Point* point_clone(Point* toBeClone){
        Point* new = new_Point(toBeClone->x, toBeClone->y);
        return new;
    }//end func

    // function to multiply the cordinate
    void point_multiply(Point* this, int numToMultiply){
        this->x = this->x * numToMultiply;
        this->y = this->y * numToMultiply;
        point_toString(this);
    }//end func
);//end class

int main(){
    
    Point* cordinate = new_Point(10, 25);
    print(cordinate->toString);
    point_multiply(cordinate, 5);
    print("The new ", cordinate->toString);
    point_free(cordinate);
    
    Array* points = new_Array(point_free);
    array_addMultiple(points,
        new_Point(10, 10),
        new_Point(20, 20),
        new_Point(30, 30),
        new_Point(40, 40)
    );
    
    for_in(x, points){
        Point* currentPoint = array_getIndexOf(points, x);
        print(currentPoint->toString);
    }//end for

    array_free(points);
    
    Map* cars = new_Map(11, string_free);
    String ferrariKey = $("Ferrari");
    String hondaKey = $("Honda");
    
    // Adding to the map
    map_add(cars, ferrariKey, $("Price of ", ferrariKey,": $300,000"));
    map_add(cars, hondaKey, $("Price of ", hondaKey, ": $20,000"));
    
    // Get the data by passing the key
    print(map_get(cars, "Ferrari"));
    print(map_get(cars, "Honda"));

    map_free(cars);
    delete(ferrariKey, hondaKey);

    Map* randomString = new_Map(20, string_free);
    int counter = 0;
    loop(x, 10){
        counter++;
        String countStr = _(counter);
        randomString->add(randomString, countStr, $("string = ", _(counter)));
        free(countStr);
    }
    counter = 0;
    for_in(x, randomString){
        counter++;
        String tempKey = _(counter);
        print("result: ", randomString->get(randomString, tempKey));
        free(tempKey); 
    }
    randomString->destroy(randomString);

    // garbage collector
    MEM_START;
        String hello = $("hello"); 
        String myName = $("my name is vic");
        String testingMem = $("testing some mem");
        String testMem2 = $("testing this thing"); 
        MEM_ADD(hello, myName, testMem2, testingMem);
        print(hello, " ", myName, " ",testingMem, " ", testMem2);
    MEM_END;

    int num = 0;
    loop(x, 5){
        num++;
        String tempStr = $("index is ", _(num));
        String tempStr2 = $("the ", tempStr);
        print(tempStr);
        // free
        delete(tempStr, tempStr2);
    }//end loop

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

    // declareing a new object
    Array* listOfString = new_Array(string_free);

    // to add object to an array
    array_add(listOfString, $("first string") );

    // to add multiple object to an array
    array_addMultiple(listOfString,
        $("second string"),
        $("third string"),
        $("fourth string"),
        $("fith string")
    );

    // you can also use 'for in' loop but data structure must have length
    for_in(x, listOfString){
        String current = array_getIndexOf(listOfString, x);
        print(current);
    }//end if

    // free
    array_free(listOfString);

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
    //testing class

}//end main
