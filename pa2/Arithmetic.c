#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BigInteger.h"
#include "List.h"
#define MAX_LINE 1024	

int main(int argc, char* argv[]){
    if( argc != 3 ){          
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    FILE *in, *out;
    int count = 0;
    char  strLine [MAX_LINE];
    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    BigInteger A;
    BigInteger B;
    char ** str = calloc(4, sizeof(char*));
    for (int i = 0; i < 4; i++){
        str[i] = calloc(MAX_LINE, sizeof(char*));
    }
    while(fgets(strLine,MAX_LINE,in)!= NULL){
        for (int j = 0; j < strlen(strLine);j++){
            str[count][j] = strLine[j];
        }
        count ++;
    }

    A = stringToBigInteger(str[1]);
    B = stringToBigInteger(str[3]);

    printBigInteger(out, A);
    fprintf(out, "\n");

    printBigInteger(out, B);
    fprintf(out, "\n");

    BigInteger S = sum(A, B);
    printBigInteger(out, S);
    fprintf(out, "\n");
    
    subtract(S, A, B);              // A - B
    printBigInteger(out,S);
    fprintf(out, "\n");

    subtract (S, A, A);              // A - A
    printBigInteger(out,S);
    fprintf(out, "\n");

    
    BigInteger three = stringToBigInteger("3");
    BigInteger two = stringToBigInteger("2");
    multiply(S, A, three);
    multiply(three, two, B);

    multiply (S, S, three);              // 3A - 2B
    fprintf(out, "\n");

    multiply(S, A, B);           // AB
    printBigInteger(out,S);
    fprintf(out, "\n");

    multiply(S, A, A);           // AA
    printBigInteger(out,S);
    fprintf(out, "\n");

    multiply(S, B, B);           // BB
    printBigInteger(out,S);
    fprintf(out, "\n");


    // 9A^4 + 16B^5
    
    freeBigInteger(&S);
    freeBigInteger(&three);
    freeBigInteger(&two);
    freeBigInteger(&A);
    freeBigInteger(&B);

    for (int i = 0; i < 4; i++){
        free(str[i]);
    }free(str);
    freeBigInteger(&A);
    freeBigInteger(&B);
    fclose(in);
    fclose(out);
    return(0);
}