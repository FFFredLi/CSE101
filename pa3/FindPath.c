/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA1
* FindPath.c
* Main function for pa3
*********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Graph.h"
#define MAX_LINE 1024	

int main(int argc, char* argv[]){
    
    // check command line for correct number of arguments
    if( argc != 3 ){          
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    int * path;
    FILE *in, *out;
    char strLine[MAX_LINE];
    char* T;
    char* T2;
    List L = newList();
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
    //while(fgets(strLine,MAX_LINE,in)!= NULL)
    
    fgets(strLine, MAX_LINE, in);                // First line;
    
    int verti = atoi(strLine);
    Graph G = newGraph(verti);
    path = calloc(2, sizeof(int));
    while(fgets(strLine,MAX_LINE,in)!= NULL){
        
        T = strtok(strLine, " ");
        T2 = strtok(NULL, " ");
        if(atoi(T) == 0 && atoi(T2) == 0){
            break;
        }
        addEdge(G, atoi(T), atoi(T2));

    }
    
    printGraph(out, G);
    
    
    while(fgets(strLine,MAX_LINE,in)!= NULL){               // part 2;
        
        T = strtok(strLine, " ");
        T2 = strtok(NULL, " ");
        
        path[0] = atoi(T);
        path[1] = atoi(T2);
        if (path[0] == 0 && path[1] == 0){
            break;
        }
        BFS(G, path[0]);
        getPath(L, G, path[1]);
        if (front(L) == 0){
            fprintf(out, "\nThe distance from %d to %d is infinity\n", path[0], path[1]);
            fprintf(out, "No %d-%d path exists\n",path[0], path[1]);
        }
        else{
            fprintf(out, "\nThe distance from %d to %d is %d\n", path[0], path[1], getDist(G,path[1]));
            fprintf(out, "A shortest %d-%d path is:",path[0], path[1]);
            printList(out,L);
            fprintf(out, "\n");
        }
        clear(L);

        //printf("The distance from %d to %d is %d\n", , ,);
        //printf("A shortest")
    }
    
    /*for(int i = 0; i < count; i++){
        BFS(G, path[i][0]);
        getPath(L, G, path[i][1]);
        if (front(L) == 0){
            fprintf(out, "\nThe distance from %d to %d is infinity\n", path[i][0], path[i][1]);
            fprintf(out, "No %d-%d path exists\n",path[i][0], path[i][1]);
        }
        else{
            fprintf(out, "\nThe distance from %d to %d is %d\n", path[i][0], path[i][1], getDist(G,path[i][1]));
            fprintf(out, "A shortest %d-%d path is:",path[i][0], path[i][1]);
            printList(out,L);
            fprintf(out, "\n");
        }
        clear(L);
    }*/

    


    freeList(&L);
    free(path);
    freeGraph(&G);
    fclose(in);
    fclose(out);
    return(EXIT_SUCCESS);
    
}