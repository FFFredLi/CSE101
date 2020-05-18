/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA5
* Dictionary.c
* Test function for PA5
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.c"

int main(){
    Dictionary D = newDictionary(1);
    Dictionary U = newDictionary(0);

    insert(D, "c", 3);
    insert(D, "a", 1);
    insert(D, "b", 2);
    delete(D, "a");
    insert(D, "e", 5);
    delete(D, "c");

    printDictionary(stdout,D);


    
}