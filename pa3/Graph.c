/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA3
* Graph.c
* Graph ADT
*********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Graph.h"
#include "List.h"
#define INF -1                      // Any negative value
#define NIL  0                     // Any non-positive;


typedef struct GraphObj{
    List* totall; 
    int * color;
    int * d;
    int * p;
    int vertex;
    int size;
} GraphObj;
/*** Constructors-Destructors ***/

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->totall = calloc(n,sizeof(List));
    G->size = 0;
    G->color = calloc(n, sizeof(int));
    G->d = calloc(n, sizeof(int));
    G->p = calloc(n,sizeof(int));
    G->vertex = n;
    for(int i = 0; i < n; i++){
        G->totall[i] = newList();
        G->color[i] = 0;
        G->d[i] = INF;
        G->p[i] = NIL;
    }
    return G;
}


void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 0; i < (*pG)->vertex ; i++){
            freeList(&(*pG)->totall[i]);
        }

        free((*pG)->totall);

        free((*pG)->p);

        free((*pG)->d);

        free((*pG)->color);

        free(*pG);
        *pG = NULL;
    }
}


/*** Access functions ***/
int getOrder(Graph G){                // Number of vertexes;
    if(G == NULL){
        printf("Graph ERROR: Calling getOrder() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->vertex;
}


int getSize(Graph G){              // Number of edges;
    if(G == NULL){
        printf("Graph ERROR: Calling getSize() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->size;

}


int getSource(Graph G){
    if(G == NULL){
        printf("Graph ERROR: Calling getSource() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < G->vertex; i++){
        if (G->d[i] == 0){
            return i+1;
        }
        else if(G->d[i] > 0){
            continue;
        }
    }
    return NIL;
}


int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph ERROR: Calling getParent() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph ERROR: Calling getParent() with an invalid argument.\n");
        exit(EXIT_FAILURE);
    }
    int parent = G->p[u - 1];
    return parent;
}


int getDist(Graph G, int u){
    if(G == NULL){
        printf("Graph ERROR: Calling getDist() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph ERROR: Calling getDist() with an invalid argument.\n");
        exit(EXIT_FAILURE);
    }
    return G->d[u - 1];
}


void getPath(List L, Graph G, int u){
    if(G == NULL){
        printf("Graph ERROR: Calling getPath() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL){
        printf("Graph ERROR: Calling getPath() without calling BFS() first.\n");
        exit(EXIT_FAILURE);
    }

    if (u == getSource(G)){
        append(L, u);
    }
    else if(G->p[u - 1] == NIL){
        append(L,NIL);
        return;
    }
    else{
        getPath(L, G, G->p[u - 1]);
        append(L, u);
    }
    
}


/*** Manipulation procedures ***/
void makeNull(Graph G){
    if(G == NULL){
        printf("Graph ERROR: Calling makeNull() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < G->vertex; i++){
        clear(G->totall[i]);
        G->color[i] = 0;
        G->d[i] = INF;
        G->p[i] = NIL;
    }
    G->size = 0;
}


void addEdge(Graph G, int u, int v){
    if(G == NULL){
        printf("Graph ERROR: Calling addEdge() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}


void addArc(Graph G, int u, int v){
    if(G == NULL){
        printf("Graph ERROR: Calling addArc() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph ERROR: Calling addArc() with invalid arguments.\n");
        exit(EXIT_FAILURE);
    }
    int fun = 0;
    List T = G->totall[v - 1];
    moveFront(T);
    
    
    /*while (index(T) != -1){
        if(get(T) == u){
            fun = 1;
            break;
        }
        moveNext(T);
    }*/



    T = G->totall[u - 1];
    if (length(T) == 0){
        append(T, v);
        G->size++;
        return;
    }
    moveFront(T);
    while(index(T) != -1){
        if (v > get(T))
            moveNext(T);
        else if (v == get(T))
            return;
        else
            break;
    }
    if (index(T) == -1){
        append(T, v);
    }
    else if (index(T) >= 0){
        insertBefore(T, v);
    }
    //append(G->totall[u - 1], v);
    if (fun == 0){
        G->size++;
    }
    
}


void BFS(Graph G, int s){
    if(G == NULL){
        printf("Graph ERROR: Calling BFS() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < G->vertex; i++){
        G->color[i] = 0;
        G->d[i] = INF;
        G->p[i] = NIL;
    }
    G->color[s - 1] = 1;
    G->d[s - 1] = 0;
    G->p[s - 1] = NIL;
    List Q = newList();
    append(Q, s);
    while (length(Q) != 0){
        int x = front(Q);
        deleteFront(Q);
        moveFront(G->totall[x - 1]);
        for (int i = 0; i < length(G->totall[x - 1]); i++){
            int temp = get(G->totall[x - 1]);              // 
            moveNext(G->totall[x - 1]);
            if (G->color[temp - 1] == 0){  // color is white.
                G->color[temp - 1] = 1;    // change it to gray.
                G->d[temp - 1] = G->d[x - 1] + 1;               // 𝑑[𝑦] = 𝑑[𝑥] + 1
                G->p[temp - 1] = x;                      //𝑝[𝑦] = x
                append(Q, temp);
            }
        }
        G->color[x - 1] = 3;
    } 
    freeList(&Q);
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if(G == NULL){
        printf("Graph ERROR: Calling printGraph() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<G->vertex; i++){
        fprintf(out, "%d: ",i + 1 );
        printList(out, G->totall[i]);
        fprintf(out,"\n");
    }

}
