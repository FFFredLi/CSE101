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
    X = diff(Ab , Bb);
    X = prod(Ab,Bb);
    printBigInteger(stdout, X);
    printf("\n");
}