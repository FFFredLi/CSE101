/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA6
* Dictionary.c
* Test function for PA6
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include"Dictionary.h"

int main(){
    int * IN = calloc(5, sizeof(int));
    Dictionary D = newDictionary(0);
    insert(D, "a", IN);
    insert(D, "b", IN);
    insert(D, "c", IN);
    insert(D, "d", IN);
    insert(D, "e", IN);
    printDictionary(stdout, D, "pre");
    //beginForward(D);
   
    delete(D, "a");
    insert(D, "f", IN);
    delete(D, "e");
    printDictionary(stdout, D, "pre");
    printf("\n");
    makeEmpty(D);
    printf("size: %d\n", size(D));

    insert(D, "x", IN);
    insert(D, "x", IN);
    insert(D, "x", IN);
    insert(D, "x", IN);
    insert(D, "x", IN);
    insert(D, "x", IN);
    insert(D, "x", IN);
    insert(D, "x", IN);
    delete(D, "x");
    delete(D, "x");
    printf("pre:\n");
    printDictionary(stdout, D, "pre");

    printf("in:\n");
    printDictionary(stdout, D, "in");

    printf("post:\n");
    printDictionary(stdout, D, "post");
    printf("\n");
    printf("size: %d\n", size(D));

    makeEmpty(D);

    insert(D, "a", IN);
    insert(D, "b", IN);
    insert(D, "c", IN);
    insert(D, "d", IN);
    insert(D, "e", IN);
    insert(D, "f", IN);
    insert(D, "g", IN);
    insert(D, "h", IN);
    insert(D, "i", IN);
    insert(D, "j", IN);
    insert(D, "k", IN);
    insert(D, "l", IN);
    insert(D, "m", IN);
    insert(D, "n", IN);

    beginForward(D);
    printf("forward:\n");
    while(currentKey(D) != KEY_UNDEF){
        printf("%s\n", currentKey(D));
        next(D);
    }
    printf("\n");
    beginReverse(D);
    printf("reverse:\n");
    while(currentKey(D) != KEY_UNDEF){
        printf("%s\n", currentKey(D));
        prev(D);
    }
    printf("\n");
    freeDictionary(&D);
    free(IN);
    
}