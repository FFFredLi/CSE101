/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA5
* DictionaryTest.c
* Test function for PA5
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

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
    
    printf("\n");
    insert(U, "a", 45);
    insert(U, "b", 2);
    insert(U, "c", 134);
    insert(U, "d", 543);
    insert(U, "e", 23);
    printDictionary(stdout,U);
    beginForward(U);
    printf("%s  ",currentKey(U));
    printf("%d\n", currentVal(U));
    next(U);
    printf("%s  ",currentKey(U));
    printf("%d\n", currentVal(U));
    next(U);
    printf("%s  ",currentKey(U));
    printf("%d\n", currentVal(U));
    next(U);
    printf("%s  ",currentKey(U));
    printf("%d\n", currentVal(U));
    
    beginReverse(U);
    printf("%s  ",currentKey(U));
    printf("%d\n", currentVal(U));

    prev(U);
    printf("%s  ",currentKey(U));
    printf("%d\n", currentVal(U));

    printf("Before Delete:\n");
    printDictionary(stdout,U);
    delete(U, "c");
    delete(U, "d");
    printf("After Delete:\n");
    printDictionary(stdout, U);

    printf("Dictionary D (%sunique keys):\n", (getUnique(D)?"":"non-"));
    printDictionary(stdout, D);
    printf("\n");

    printf("forward D:\n");
    for(int x=beginForward(D); currentVal(D)!=VAL_UNDEF; x=next(D)){
        printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(D), x);
    }
    
    printf("\n");

    printf("reverse U:\n");
    for(int y=beginReverse(U); currentVal(U)!=VAL_UNDEF; y=prev(U)){
        printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(U), y);
    }
   printf("\n\n");
    freeDictionary(&D);
    freeDictionary(&U);
    return 0;
}