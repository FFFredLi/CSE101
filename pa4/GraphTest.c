/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA4
* GraphTest.c
* Test function for pa4
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL;
   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 2,3);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,4);
   addArc(G, 3,7);
   addArc(G,4,3);
   addArc(G,4,8);
   addArc(G,5,1);
   addArc(G,5,6);
   addArc(G, 6,7);
   addArc(G,7,6);
   addArc(G,7,8);
   addArc(G, 8,8);

   printGraph(stdout, G);

   DFS(G, S);

   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);

   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);

   return(0);
}


