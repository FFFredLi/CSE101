/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA2
* List.c
* List ADT
*********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "List.h"



typedef struct NodeObj{
    // Some code;
    long index;
    struct NodeObj* next;
    struct NodeObj* previous;
} NodeObj;

typedef NodeObj* Node;


Node newNode(long number){
    Node N;
    N = malloc(sizeof(NodeObj));

    if (N == NULL){
        printf("Can't allocate mem data\n");
        exit(EXIT_FAILURE);
    }

    N->index = number;
    N->next = NULL;
    N->previous = NULL;
    // Some code
    return N;
    
}

void freeNode(Node* pN){
    if (pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

typedef struct ListObj{
    Node front;
    Node back;
    // Node temp;
    int totalNumber;
    Node cursor;
} ListObj;


List newList(void){
    List L = malloc(sizeof(ListObj));

    L -> front = NULL;
    L -> back = NULL;
    // L -> temp = NULL;
    L -> totalNumber = 0;   // Length of the List.
    L -> cursor = NULL;     // initial cursor.
    return L;
}


void deleteAll(Node R){
   if( R!=NULL ){
      deleteAll(R->next);
      freeNode(&R);
   }
}


void dequeueAll(List Q){
   if( Q==NULL ){
      fprintf(stderr, "IntegerQueue Error: dequeueAll() called on NULL "\
                      "IntegerQueue reference");
      exit(EXIT_FAILURE);
   }

   Q->totalNumber = 0;
   deleteAll(Q -> front);
   
   Q -> front = Q->back = NULL;
   Q ->cursor = NULL;
}


void freeList(List* pL){
    // Code...
    if (pL!=NULL && *pL!=NULL){
        dequeueAll(*pL);
        free(*pL);
        *pL = NULL;
    }

}


int length(List L){
    if (L == NULL){
        printf("List Error: calling length() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    return L->totalNumber;
}


int index(List L){
    if (L == NULL){
        printf("List Error: calling index() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    int i;
    if (L->cursor == NULL)
        return -1;
    else{
        Node N = L ->front;
        i = 0;
        while (N != L->cursor){
            i++;
            N = N->next;  
        }
        return i;
    }
}


long front(List L){
    if (L == NULL){
        printf("List Error: calling front() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }

    if(L->totalNumber > 0)
        return L->front->index;
    printf("List Error: calling front() in an empty list.\n");
    exit(EXIT_FAILURE);
}


long back(List L){
    if (L == NULL){
        printf("List Error: calling back() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (L->totalNumber > 0)
        return L->back->index;
    printf("List Error: calling back()in an empty list.\n");
    exit(EXIT_FAILURE);
}


long get(List L){
    if (L == NULL){
        printf("List Error: calling get() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if(length(L)==0){
        printf("List Error: calling get() on an empty List.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L)<0){
        printf("List Error: calling get() on an undefined cursor.\n");
        exit(EXIT_FAILURE);
    }

    return L->cursor->index;
}


int equals(List A, List B){
    if (A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }

    Node N = A->front;
    Node M = B->front;
    int eq = (A->totalNumber == B->totalNumber);
    while (eq && N!=NULL){
        eq = (N->index == M->index);
        N = N->next;
        M = M->next;
    }
    return eq;
    

    
}



// Manipulation procedures ----------------------------------------------------
void clear(List L){// Resets L to its original empty state.
    if (L == NULL){
        printf("List Error: calling clear() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    dequeueAll(L);

    // Code..

} 


void moveFront(List L){
    if (L == NULL){
        printf("List Error: calling moveFront() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    // If L is non-empty, sets cursor under the front element,
    // otherwise does nothing.
    if (L->totalNumber != 0)
        L->cursor = L->front;

    
} 
 

void moveBack(List L){
    if (L == NULL){
        printf("List Error: calling moveBack() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    // If L is non-empty, sets cursor under the back element,
    // otherwise does nothing.
    if (L->totalNumber != 0)
        L->cursor = L->back;
} 
 

void movePrev(List L) {
    if (L == NULL){
        printf("List Error: calling movePrev() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor->previous;
    }
    else if (L->cursor != NULL && L->cursor == L->front){
        L->cursor = NULL;
    }
 // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
}


void moveNext(List L){ 
    if (L == NULL){
        printf("List Error: calling moveNext() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor->next;
    }
    else if(L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL;
    }
 // If cursor is defined and not at back, move cursor one step toward the back of L; 
 // if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
}



void prepend(List L, long data){
    if (L == NULL){
        printf("List Error: calling prepend() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    // Insert new element into L. If L is non-empty,
    // insertion takes place before front element.
    Node N = newNode(data);

    if (L->totalNumber == 0){
        L->front = L->back = N;
    }
    else {
        L->front->previous = N;                   //
        N->next = L->front;
        L->front = N;
    }
    L->totalNumber++;
    
} 


void append(List L, long data){// Insert new element into L. If L is non-empty,
    // insertion takes place after back element.
    if (L == NULL){
        printf("List Error: calling append() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(data);
    if (L->totalNumber == 0){
        L->front = L->back = N;
    }
    else{
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->totalNumber ++;
} 


void insertBefore(List L, long data){// Insert new element before cursor.
    // Pre: length()>0, index()>=0
    if (L == NULL){
        printf("List Error: calling insertBefore() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List Error: calling insertBefore() on an empty List .\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("List Error: calling insertBefore() without defined cursor.\n");
        exit(EXIT_FAILURE);
    }
    
    Node N = newNode(data);
    N->next = L->cursor;
    N->previous = L->cursor->previous;

    if(L->cursor->previous != NULL){
        L->cursor->previous->next = N;
    }
    if (L->front == L->cursor){
        L->front = N;
    }
    L->cursor->previous = N;
    L->totalNumber++;
} 


void insertAfter(List L, long data){// Insert new element after cursor.
    // Pre: length()>0, index()>=0
    if (L == NULL){
        printf("List Error: calling insertAfter() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List Error: calling insertAfter() on an empty List .\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("List Error: calling insertAfter() without defined cursor.\n");
        exit(EXIT_FAILURE);
    }
    // Code...
    Node N = newNode(data);

    N->previous = L->cursor;
    N->next = L->cursor->next;

    if (L->cursor->next != NULL){
        L->cursor->next->previous = N;
    }

    if (L->cursor == L->back){
        L->back = N;
    }
    L->cursor->next = N;
    L->totalNumber++;
} 


void deleteFront(List L){    // Delete the front element. Pre: length()>0
    if (L == NULL){
        printf("List Error: calling deleteFront() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List Error: calling deleteFront() on an empty List .\n");
        exit(EXIT_FAILURE);
    }
    // Code...
    Node N = L->front;
    if(length(L) == 1){
        clear(L);

    }
    else if (length(L) == 2){
        
        L->front = L->back = N->next;
        L->front->previous = NULL; 
        freeNode(&N);
        L->totalNumber--;
    }
    else{
        if(L->cursor == L->front){
            L->cursor = NULL;
        }
        
        L->front = N->next;
        L->front->previous = NULL;
        freeNode(&N);
        L->totalNumber--;
    }
    
} 


void deleteBack(List L){    // Delete the back element. Pre: length()>0
    if (L == NULL){
        printf("List Error: calling deleteBack() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List Error: calling deleteBack() on an empty List .\n");
        exit(EXIT_FAILURE);
    }
    // Code...
    Node N = L->back;
    if(length(L)==1){
        clear(L);
        
        
    }
    else{
        if(L->cursor == L->back){
            L->cursor = NULL;
        }
        L->back = N->previous;
        L->back->next = NULL;
        freeNode(&N);  
        L->totalNumber--;
    }
    
} 


void delete(List L){
    // Delete cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0
    if (L == NULL){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0){
        printf("List Error: Calling delete() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (index < 0){
        printf("List Error: Calling delete() on an undefined cursor element. \n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 1){
        freeNode(&L->cursor);
        L->front=L->back = NULL;
        L->cursor = NULL;
        L->totalNumber--;
    }
    else if(L->cursor == L->front){
        deleteFront(L);
        L->cursor = NULL;
    }
    else if(L->cursor == L->back){
        deleteBack(L);
        L->cursor = NULL;
    }
    else{
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        freeNode(&L->cursor);
        L->cursor = NULL;
        L->totalNumber--;
    }
    
} 


void printList(FILE* out, List L){
    if (L == NULL){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    Node N = NULL;
    
    for (N = L->front; N != NULL; N = N->next){
        if (N->index == 0 && N == L->front)
            continue;
        if (N == L->front){
            fprintf(out,"%ld",N->index);
        }
        else{
            fprintf(out,"%09ld",N->index);
        }
        
    }
    //fprintf(out,"\n");
    

}


List copyList(List L){
    if (L == NULL){
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    List copy = newList();
    Node N;
    
    for (N = L->front; N != NULL; N = N->next){
        append(copy,N->index);
    }

    return copy;
}


List concatList(List A, List B){
    // Returns a new List which is the concatenation of A and B. 
    // The cursor in the new List is undefined,  
    // regardless of the states of the cursors in A and B. 
    // The states of A and B are unchanged. 
    if (A == NULL || B == NULL){
        printf("List Error: calling concatList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List concat = newList();
    Node N;
    for (N= A->front; N != NULL; N = N->next){
        append(concat, N->index);
    }
    for (N = B->front; N != NULL; N = N->next){
        append(concat, N->index);
    }
    return concat;
}


void set(List L, long x){
    if (L == NULL){
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("List Error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling set() without setting cursor.\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    Node T = L->cursor;
    if(length(L) == 1){
        L->back = L->front = L->cursor = N;
    }
    else if (T = L->front){
        
        N->next = T->next;
        T->next->previous = N;
        L->front = N;
        L->cursor = N;
    }
    else if (T = L->back){
        T->previous->next = N;
        N->previous = T->previous;
        L->back = N;
        L->cursor = N;
    }
    else{
        N->next = T->next;
        N->previous = T->previous;
        T->previous->next = N;
        T->next->previous = N;
        L->cursor = N;
    }
   
    freeNode(&T);
}