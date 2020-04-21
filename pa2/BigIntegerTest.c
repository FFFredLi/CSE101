/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA1
* BigIntegerTest
* BigIntegerTest for pa2
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"BigInteger.h"

int main(){
    char* A = "+1242342";
    char* B = "-6432";
    BigInteger Ab = stringToBigInteger(A);
    BigInteger Bb = stringToBigInteger(B);

    
    BigInteger X;
    X = sum(Bb,A);
    
    X = sum(Ab,Bb);
    printBigInteger(stdout, X);
    printf("\n");

    X = diff(Ab , Bb);
    printBigInteger(stdout, X);
    printf("\n");
    X = prod(Ab,Bb);
    printBigInteger(stdout, X);
    printf("\n");

    negate(Ab);
    printBigInteger(stdout, Ab);
    printf("\n");

    printf("Equals: %d\n",equals(Ab,Bb));

    freeBigInteger(&Ab);
    freeBigInteger(&Bb);
    freeBigInteger(&X);

}