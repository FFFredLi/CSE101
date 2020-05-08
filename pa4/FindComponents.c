/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA1
* FindComponents.c
* Main function for pa4
*********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Graph.h"

#define MAX_LINE 1024	

int main(int argc, char* argv[]){
     if( argc != 3 ){          
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    char* T;
    char* T2;
    int strong = 0;
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    char strLine[MAX_LINE];
    fgets(strLine, MAX_LINE, in);
    int verti = atoi(strLine);
    Graph G = newGraph(verti);


    // First Part.
    while(fgets(strLine,MAX_LINE,in)!= NULL){
        T = strtok(strLine, " ");
        T2 = strtok(NULL, " ");
        if(atoi(T) == 0 && atoi(T2) == 0)
            break;
        addArc(G, atoi(T), atoi(T2));
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);


    // Second Part.  
    List L = newList();
    List Temp = newList();
    for (int i = 0; i < verti; i++)
        append(L, i+1);

    DFS(G, L);

    fprintf(out,"\n");
    Graph Tr = transpose(G);
    DFS(Tr, L);

    for (int i = 0; i < verti; i++){
        if (getParent(Tr,i+1) == 0)
            strong++;
    }
    fprintf(out,"\nG contains %d strongly connected components:\n",strong);
    moveBack(L);
    for (int i = 0; i<strong; i++){
        
        while(getParent(Tr,get(L)) != 0){
            prepend(Temp,get(L));
            movePrev(L);
        }
        prepend(Temp, get(L));
        movePrev(L);
        

        fprintf(out,"Component %d: ", i+1);
        printList(out, Temp);
        fprintf(out, "\n");
        clear(Temp);
        // code...
    }



    fclose(in);
    fclose(out);
    freeList(&L);
    freeGraph(&Tr);
    freeGraph(&G);
    return(EXIT_SUCCESS);
    

}
