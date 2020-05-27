/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA6
* Order.c
* Main function for PA6
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
    int n = 0;
    FILE *in, *out;
    char strLine[MAX_LINE];
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
    char** strList; 
    while(fgets(strLine,MAX_LINE,in)!= NULL){
        n++;
    }
    strList = calloc(n, sizeof(char*));
    rewind(in);
    for (int i = 0; i < n; i++)
        strList[i] = calloc(MAX_LINE,sizeof(char));
    
    int index = 0;
    while(fgets(strLine,MAX_LINE,in)!= NULL){
        for (int i = 0; i<strlen(strLine); i++){
            strList[index][i] = strLine[i];
        }
        index++;
    }
    
    Dictionary D = newDictionary(0);
    for (int i = 0; i < n; i++){
        insert(D, strList[i], NULL);
    }

    fprintf(out, "******************************************************\nPRE-ORDER:\n******************************************************\n");
    printDictionary(out, D, "pre");
    fprintf(out, "\n\n");

    fprintf(out, "******************************************************\nIN-ORDER:\n******************************************************\n");
    printDictionary(out, D, "in");
    fprintf(out, "\n\n");
    
    fprintf(out, "******************************************************\nPOST-ORDER:\n******************************************************\n");
    printDictionary(out, D, "post");
    fprintf(out, "\n\n");
    for(int i = 0; i < n; i++){
        free(strList[i]);
    }free(strList);
    freeDictionary(&D);
    fclose(in);
    fclose(out);
    return(EXIT_SUCCESS);
}