/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA3
* GraphTest.c
* Test File for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){

   List  L = newList(); // central vertices 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(6);

   addEdge(G, 1, 2);
   addEdge(G, 1, 3);
   printf("Size: %d\n", getSize(G));
   addEdge(G, 2, 1);
   addEdge(G, 2, 4);
   addEdge(G, 2, 5);
   addEdge(G, 2, 6);
   printf("Size: %d\n", getSize(G));
   addEdge(G, 3, 1);
   addEdge(G, 3, 4);
   printf("Size: %d\n", getSize(G));
   addEdge(G, 4, 2);
   addEdge(G, 4, 3);
   addEdge(G, 4, 5);
   printf("Size: %d\n", getSize(G));
   addEdge(G, 5, 2);
   addEdge(G, 5, 4);
   addEdge(G, 5, 6);
   printf("Size: %d\n", getSize(G));
   addEdge(G, 6, 2);
   addEdge(G, 6, 5);
   
   // Print adjacency list representation of G
   printGraph(stdout, G);

   printf("Size: %d\n", getSize(G));

   BFS(G, 3);

   getPath(L, G, 6);

   printList(stdout, L);


   // Print results 


   // Free objects 

   freeList(&L);
   freeGraph(&G);

   return(0);
}
