/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA4
* Graph.c
* Graph ADT
*********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "List.h"
#include "Graph.h"

int time;

typedef struct GraphObj{
    List* totall; 
    int * color;
    int * d;
    int * p;
    int * f;
    int vertex;
    int size;
} GraphObj;


// Constructors-Destructors
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->totall = calloc(n,sizeof(List));
    G->color = calloc(n, sizeof(int));
    G->d = calloc(n,sizeof(int));
    G->p = calloc(n, sizeof(int));
    G->f = calloc(n,sizeof(int));
    G->size = 0;
    G->vertex = n;

    for(int i = 0; i < n; i++){ // Initial
        G->totall[i] = newList();
        G->color[i] = 0;
        G->d[i] = UNDEF;
        G->f[i] = UNDEF;
        G->p[i] = NIL;
    }       
        
    return G;
}


void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 0; i < (*pG)->vertex ; i++)
            freeList(&(*pG)->totall[i]);
        free((*pG)->totall);
        free((*pG)->p);
        free((*pG)->d);
        free((*pG)->f);
        free((*pG)->color);
        free(*pG);
        *pG = NULL;
    }
}

// Access functions
int getOrder(Graph G){
    if(G == NULL){
        printf("Graph ERROR: Calling getOrder() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->vertex;
}


int getSize(Graph G){
    if(G == NULL){
        printf("Graph ERROR: Calling getSize() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}


int getParent(Graph G, int u){/* Pre: 1<=u<=n=getOrder(G) */
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


int getDiscover(Graph G, int u){/* Pre: 1<=u<=n=getOrder(G) */
    if(G == NULL){
        printf("Graph ERROR: Calling getDiscover() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph ERROR: Calling getDiscover() with an invalid argument.\n");
        exit(EXIT_FAILURE);
    }
    return G->d[u - 1];
} 


int getFinish(Graph G, int u){/* Pre: 1<=u<=n=getOrder(G) */
    if(G == NULL){
        printf("Graph ERROR: Calling getFinish() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph ERROR: Calling getFinish() with an invalid argument.\n");
        exit(EXIT_FAILURE);
    }
    return G->f[u - 1];
} 


// Manipulation procedures
void addArc(Graph G, int u, int v){/* Pre: 1<=u<=n, 1<=v<=n */
    if(G == NULL){
        printf("Graph ERROR: Calling addArc() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph ERROR: Calling addArc() with invalid arguments.\n");
        exit(EXIT_FAILURE);
    }
    List T;
    T = G->totall[u - 1];
    if (length(T) == 0){
        append(G->totall[u - 1], v);
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
    if (index(T) == -1)
        append(T, v);
    else if (index(T) >= 0)
        insertBefore(T, v);
    G->size++;
} 


void addEdge(Graph G, int u, int v){/* Pre: 1<=u<=n, 1<=v<=n */
    if(G == NULL){
        printf("Graph ERROR: Calling addEdge() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph ERROR: Calling addEdge() with invalid arguments.\n");
        exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
} 


void visit(Graph G,List S, int i){
    G->d[i] = ++time;
    G->color[i] = 1;
    moveFront(G->totall[i]);
    while (index(G->totall[i]) != -1){
        if(G->color[get(G->totall[i]) - 1]  == 0){
            G->p[get(G->totall[i]) - 1] = i + 1;
            visit(G, S, get(G->totall[i]) - 1);
        }
        moveNext(G->totall[i]);
    }
    G->color[i] = 2;
    G->f[i] = ++time;
    insertAfter(S, i+1);
    

    

}

void DFS(Graph G, List S){/* Pre: length(S)==getOrder(G) */
    if(G == NULL){
        printf("Graph ERROR: Calling DFS() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if(S == NULL){
        printf("Graph ERROR: Calling DFS() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if(length(S) != getOrder(G)){
        printf("Graph ERROR: Calling DFS() on invalid List length.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < G->vertex; i++){
        G->color[i] = 0;
        G->p[i] = NIL;      // NIL
        //G->f[i] = NIL;
        //G->d[i] = UNDEF;
        
    }
    moveBack(S);
    time = 0;
    for (int i = 0; i < G->vertex; i++){
        if(G->color[front(S) - 1] == 0)
            visit(G,S,front(S) - 1);
        deleteFront(S);
        
    }
} 


// Other Functions
Graph transpose(Graph G){
    if(G == NULL){
        printf("Graph ERROR: Calling transpose() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    Graph trans = newGraph(G->vertex);
    trans->vertex = G->vertex;
    for (int i = 0; i < G->vertex; i++){
        trans->d[i] = UNDEF;
        trans->f[i] = UNDEF;
        trans->p[i] = NIL;
    }

    for (int i = 0; i < G->vertex; i++){

        moveFront(G->totall[i]);
        while(index(G->totall[i]) != -1){
            int temp = get(G->totall[i]);
            addArc(trans, temp , i + 1);
            moveNext(G->totall[i]);
        }
    }

    return trans;
}


Graph copyGraph(Graph G){
    if(G == NULL){
        printf("Graph ERROR: Calling copyGraph() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    Graph copy = newGraph(G->vertex);
    copy->vertex = G->vertex;
    copy->size = G->size;
    for(int i = 0; i < G->vertex; i++){
        copy->color[i] = G->color[i];
        copy->d[i] = G->d[i];
        copy->p[i] = G->p[i];
        copy->f[i] = UNDEF;
        freeList(&copy->totall[i]);
        copy->totall[i] = copyList(G->totall[i]);
    }
    return copy;
    
}

void printGraph(FILE* out , Graph G){
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