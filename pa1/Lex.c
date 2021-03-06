/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA1
* Lex.c
* Main function for pa1
*********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "List.h"
#define MAX_LINE 1024	

void print(FILE* out, char** st, List L){
    moveFront(L);
    while(index(L) != -1){
        fprintf(out, st[get(L)]);
        moveNext(L);
    }
}

int main(int argc, char* argv[]){
    // check command line for correct number of arguments
    if( argc != 3 ){          
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    int n = 0;
    int count = 0;
    FILE *in; 
    FILE *out;
    
    List L = newList();
    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    char strLine[MAX_LINE];
    
    
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
    
    printf("%d",count);
    char** strL = calloc(count,sizeof(char*));
    for (int i = 0; i < count; i++){
        strL[i] = calloc(MAX_LINE,sizeof(char));
    }

    while(fgets(strLine,MAX_LINE,in)!= NULL){
        //char * T = malloc(sizeof(char)*100);
        for (int j = 0; j < strlen(strLine);j++){
            strL[n][j] = strLine[j];
        }
        //strL[n] = T;
        n++;
        
    }





    // creat a index list.
    
    for (int i = 0; i < count; i++){
        if(i == 0){
            append(L, i);
        }
        else{
            moveFront(L);
            
  
            while(index(L) != -1 && strcmp(strL[i], strL[get(L)] )> 0 ){
 
                moveNext(L);
            }
            if (index(L) == -1){
                append(L,i);
            }
            else if (index >= 0){
                insertBefore(L, i);
            }
            
        }
    }

    moveFront(L);

    while(index(L) != -1){
        //for (int i = 0; i < strlen(strL[get(L)]); i++){
        //    fprintf(out, "%c", strL[get(L)][i]);
        //}
        int x = get(L);
        fprintf(out, "%s", strL[x]);
        //fflush(out);
        moveNext(L);
    }



    for (int i = 0; i < count ; i++){
        free(strL[i]);
    }free(strL);
    //free(strLine);
    freeList(&L);
    fclose(in);
    fclose(out);
    return(0);
}