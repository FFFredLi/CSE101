/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA5
* Lex.c
* Main function for PA5
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"
#define MAX_LINE 1024	


int main(int argc, char* argv[]){
    // check command line for correct number of arguments
    if( argc != 3 ){          
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    int n, count = 0;
    FILE *in, *out;
    char * strLine = calloc(MAX_LINE,sizeof(char));
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
    while(fgets(strLine,MAX_LINE,in)!= NULL){
        count++;
    }
    rewind(in);

    char** strL = calloc(count, sizeof(char*) );
    for (int i = 0; i < count; i++){
        strL[i] = calloc(MAX_LINE,sizeof(char));
    }
    n = 0;
    while(fgets(strLine,MAX_LINE,in)!= NULL){
        //printf("strLine : %s\n", strLine);
        for (int i = 0; i<strlen(strLine); i++){
            strL[n][i] = strLine[i];
        }
        n++;
    }
    
    Dictionary D = newDictionary(0);
    for (int i = 0; i < count; i++){
        insert(D, strL[i], i);
    }
    
    beginForward(D);
    while (currentKey(D) != KEY_UNDEF){
        fprintf(out, strL[currentVal(D)]);
        next(D);
    }
    



    freeDictionary(&D);
    free(strLine);
    for (int i = 0; i < count; i++){
        free(strL[i]);
    }free(strL);
    fclose(in);
    fclose(out);
    return(0);
}
