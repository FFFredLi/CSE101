/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA6
* Dictionary.c
* Dictionary ADT
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

#define BLACK 0
#define RED 1

//-------------------------------------------------------------------------------------------------
// Node Functions;

typedef struct NodeObj{
    KEY_TYPE key;
    VAL_TYPE val;
    int color;
    struct NodeObj* left;
    struct NodeObj* right;
    struct NodeObj* parent;
} NodeObj;
typedef NodeObj* Node;

Node newNode(KEY_TYPE key, VAL_TYPE val){
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL){
        printf("Can't allocate mem data\n");
        exit(EXIT_FAILURE);
    }
    N->key = key;
    N->val = val;
    N->color = RED;
    N->parent=NULL;
    N->left = NULL;
    N->right = NULL;
    return N;
}

void freeNode(Node* pN){
    if (pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

void deleteAll(Node R){
   if( R!=NULL ){
      deleteAll(R->left);
      deleteAll(R->right);
      freeNode(&R);
   }
}

//---------------------------------------------------------------------------
// Help function:
Node findLeft(Node N){
    Node L;
    if (N->left != NULL){
        L = findLeft(N->left);
    }
    else
        return N;
    return L;
}

Node findright(Node N){
    Node R;
    if (N->right != NULL){
        R = findright(N->right);
    }
    else 
        return  N;
    return R;
}

Node findKey(Node R, char* k){
    if(R==NULL || strcmp(k, R->key)==0) 
        return R;
    if( strcmp(k, R->key)<0 ) 
        return findKey(R->left, k);
    else // strcmp(k, R->key)>0
        return findKey(R->right, k);
}

//-----------------------------------------------------------------------
// Dictionay Function
typedef struct DictionaryObj{
    int size;
    int unique;
    Node root;
    Node cursor;
}DictionaryObj;

Dictionary newDictionary(int unique){
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->size = 0;
    D->root = NULL;
    D->cursor = NULL;
    D->unique = unique;
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
    if( pD!=NULL && *pD!=NULL ){
        makeEmpty(*pD);
        free(*pD);
        *pD = NULL;
   }
}


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling size() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling getUnique() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    return D->unique;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    if (D==NULL){
        printf("Dictionary ERROR: Calling lookup() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    Node temp;
    temp = findKey(D->root, k);
    if (temp == NULL){
        return VAL_UNDEF;
    }
    else
        return temp ->val;
}


// Manipulation procedures ----------------------------------------------------
// rotateLeft()
void rotateLeft(Dictionary D, Node N ){
    if (N == NULL){
        printf("Dictionary ERROR: Calling rotateLeft() on NULL Node.\n");
        exit(EXIT_FAILURE);
    }
    Node R = N->right;
    N->right = R->left;
    if (R->left != NULL){
        R->left->parent = N;
    }
    R->parent = N->parent;
    if (N->parent == NULL){
        D->root = R;
    }
    else if (N->parent->left == N)
        N->parent->left = R;
    else 
        N->parent->right = R;
    R->left = N;
    N->parent = R;
}

// RotateRight()
void rotateRight(Dictionary D,Node N){
    if (N == NULL){
        printf("Dictionary ERROR: Calling rotateRight() on NULL Node.\n");
        exit(EXIT_FAILURE);
    }
    Node L = N->left;
    N->left = L->right;
    if (L->right != NULL)
        L->right->parent = N;
    L->parent = N->parent;
    if (N->parent == NULL)
        D->root = L;
    else if (N->parent->right == N)
        N->parent->right = L;
    else
        N->parent->left = L;
    L->right = N;
    N->parent = L;
    
}

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    if (D==NULL){
        printf("Dictionary ERROR: Calling insert() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    if (getUnique(D) == 1){
        if (lookup(D, k) != VAL_UNDEF){
            printf("Dictionary ERROR: Calling insert() to insert same key.\n");
            exit(EXIT_FAILURE);
        }
    }
    Node N = newNode(k, v);
    Node B = NULL;
    Node A = D->root;
    while(A != NULL){                   // Find parent key.
        B = A;
        if (strcmp(k, A->key) < 0)
            A = A->left;
        else
            A = A->right;
    }
    if (B == NULL)                      // Dictionary is empty.
        D->root = N;
    else if (strcmp(k, B->key) < 0){    //KEY_CMP(k, B->key)
        N->parent = B;
        B->left = N;
    }   
    else{
        N->parent = B;
        B->right = N;
    }
    D->size++;                // Size +1

    // ---------------------------------------------------------------------------
    // Rotate if necessary
    // 
    while (N != NULL && N != D->root && N->parent->color == RED){
        if(N->parent == N->parent->parent->left){
            A = N->parent->parent->right;
            if(A!= NULL && A->color == RED){
                N->parent->color = BLACK;
                A->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else{
                if (N == N->parent->right){
                    N = N->parent;
                    rotateLeft(D, N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                rotateRight(D, N->parent->parent);
            }
        }
        else{
            A = N->parent->parent->left;
            if (A != NULL && A->color == RED ){
                N->parent->color = BLACK;
                A->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else{
                if( N == N->parent->left){
                    N = N->parent;
                    rotateRight(D, N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                rotateLeft(D, N->parent->parent);
            }
        }
    }

    D->root->color = BLACK;
}



void adjustDelete(Dictionary D, Node N){
    Node A = NULL;
    while (N != D->root && N->color == BLACK){
        if (N == N->parent->left){
            A = N->parent->right;
            // Left Rotate:

            if (A->color == RED){
                A->color = BLACK;
                N->parent->color = RED;
                rotateLeft(D, N->parent);
                A = N->parent->right;
            }
            
            if((A->left == NULL||A->left->color == BLACK ) && (A->right == NULL||A->right->color == BLACK)){
                A->color = RED;
                N = N->parent;
            }
            else{
                if(A->right == NULL || A->right->color == BLACK){
                    A->left->color = BLACK;
                    A->color = RED;
                    rotateRight(D, A);
                    A = N->parent->right;
                }

                A->color = N->parent->color;
                N->parent->color = BLACK;
                A->right->color = BLACK;
                rotateLeft(D, N->parent);
                N = D->root;
            }
        }
        else{
            A = N->parent->left;
            if (A->color == RED){
                A->color = BLACK;
                N->parent->color = RED;
                rotateRight(D, N->parent);
                A = N->parent->left;
            }

            if ((A->right == NULL || A->right->color == BLACK) && (A->left == NULL||A->left->color == BLACK)){
                A->color = RED;
                N = N->parent;
            }
            else{
                if ( A->left == NULL||A->left->color == BLACK  ){
                    A->right->color = BLACK;
                    A->color = RED;
                    rotateLeft(D, A);
                    A = N->parent->left;
                }
                A->color = N->parent->color;
                N->parent->color = BLACK;
                A->left->color = BLACK;
                rotateRight(D, N->parent);
                N = D->root;
            }
        }
    }
    N->color = BLACK;
}


// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
    if (D==NULL){
        printf("Dictionary ERROR: Calling delete() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    
    if( lookup(D,k) ==VAL_UNDEF ){
            fprintf(stderr, 
                "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
            exit(EXIT_FAILURE);
        }

    Node P = NULL;
    Node N = findKey(D->root, k);
    if (D->cursor == N){
        D->cursor = NULL;
    }
    
    if( N->left==NULL && N->right==NULL ){  // case 1 (no children)
        
        if( N==D->root ){
            D->root = NULL;
            freeNode(&N);
        }
        else{
            
            P = N->parent;
            if (N->color == BLACK)
                adjustDelete(D, N);   
            if( P->right==N )
                P->right = NULL;
            else
                P->left = NULL;

             
            freeNode(&N);
        }
    }

    else if(N->right == NULL){
        if(N == D->root){
            D->root = N->left;
            D->root->parent =NULL;
            freeNode(&N);
        }
        else{
            if (N->color == BLACK)
                adjustDelete(D, N);
            P = N->parent;
            
            if( P->right==N ){
                P->right = N->left;
                if (N ->left != NULL)
                    N->left->parent = P;
            }
            else{
                P->left = N->left;
                if (N ->left != NULL)
                    N->left->parent = P;
            }
            
            freeNode(&N);
        }
    }

    else if(N->left == NULL){
        if (N == D->root){
            D->root = N->right;
            D->root->parent = NULL;
            freeNode(&N);
        }
        else{
            if (N->color == BLACK)
                adjustDelete(D, N);
            P = N->parent;
             
            if (P ->right == N ){
                
                P->right = N->right;
                if (N->right != NULL)
                    N->right->parent = P;
                
            }
                
            else{
                P->left = N->right;
                if (N->right != NULL)
                    N->right->parent = P;
                
            }
            
            freeNode(&N);
        }
    }
    else{// case4: (two children: N->left!=NULL && N->right!=NULL)
        // Code....
        Node T = findLeft(N->right);
        N->key = T->key;
        N->val = T->val;
        P = T->parent;
        if (T->color == BLACK)
            adjustDelete(D, T);
        if(P->left == T){
            P->left = T->right ;
            if (T->right != NULL)
                T->right->parent = P;
        }
        else{
            P->right = T->right;
            if (T->right != NULL)
                T->right->parent = P;
            
        }
        freeNode(&T);
    }
    
    D->size--;
    // ---------------------------------------------------------------------------
    // Rotate if necessary
    // 
    
    
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling makeEmpty() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    deleteAll(D->root);
    D->cursor = NULL;
    D->root = NULL;
    D->size = 0;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling beginForward() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    if(size(D) == 0)
        return VAL_UNDEF;
    else{
        //Code...
        Node N = findLeft(D->root);
        D->cursor = N;
        return N->val;
    }
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling beginReverse() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    if (D->size == 0)
        return VAL_UNDEF;
    else{
        //code...
        Node N = findright(D->root);
        D->cursor = N;
        return N->val;
    }
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling currentKey() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    if (D->cursor == NULL)
        return KEY_UNDEF;
    else 
        return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling currentVal() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    if (D->cursor == NULL)
        return VAL_UNDEF;
    else 
        return D->cursor->val;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling next() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    
    if (D->cursor == NULL)                 // no iteration
        return VAL_UNDEF;
    else{Node T = NULL;
        Node N = findright(D->root);
        if (D->cursor == N){                // reached the last pair,
            D->cursor = NULL;
            return VAL_UNDEF;
        }
        //Code...                           // Middle....
        if (D->cursor->right != NULL){
            T = findLeft(D->cursor->right);
            D->cursor = T;
            return T->val;
        }
        
        // Right == NULL;
        T = D->cursor->parent;
        if (T->left == D->cursor){
            D->cursor = T;
            return D->cursor->val;
        }
        Node X = D->cursor;
        T = D->cursor->parent;
        while(T->left != X){  //T->left != X
            X = T;
            T = T->parent;
        }
        D->cursor = T;
        return T->val;

    }
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D){
    if (D==NULL){
        printf("Dictionary ERROR: Calling prev() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    Node T;
    Node X;
    if (D->cursor == NULL)                   // no iteration is underway
        return VAL_UNDEF;
    else{
        Node N = findLeft(D->root);
        if (N == D->cursor){                //// reached the first pair,
            D->cursor = NULL;
            return VAL_UNDEF;
        }
        // Code ....                        // Middle...

        if (D->cursor->left != NULL){
            T = findright(D->cursor->left);
            D->cursor = T;
            return T->val;
        }

        //Left == NULL;
        T = D->cursor->parent;
        
        X = D->cursor;
        
        while(T->right != X){
            
            X = T;
            T = T->parent;

        }
        D->cursor = T;
        return D->cursor->val;
    }
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printPre(FILE* out, Node N){
    if (N == NULL)
        return;
    fprintf(out, "%s", N->key);
    printPre(out, N->left);
    printPre(out, N->right);
}

void printIn(FILE* out, Node N){
    if (N == NULL)
        return;
    printIn(out, N->left);
    fprintf(out, "%s", N->key);
    printIn(out, N->right);
}

void printPost(FILE* out, Node N){
    if (N == NULL)
        return;
    printPost(out, N->left);
    printPost(out, N->right);
    fprintf(out, "%s", N->key);
}

void printDictionary(FILE* out, Dictionary D, const char* ord){
    if (D==NULL){
        printf("Dictionary ERROR: Calling printDictionary() on NULL Graph Dictionary.\n");
        exit(EXIT_FAILURE);
    }
    int result_1 = KEY_CMP(ord, "pre");
    int result_2 = KEY_CMP(ord, "in");
    int result_3 = KEY_CMP(ord, "post");
    if (result_1 == 0){ // Pre order
        printPre(out, D->root);
    }
    else if (result_2 == 0){  // In order
        printIn(out, D->root);
    }
    else if (result_3 == 0){  // Post order
        printPost(out, D->root);
    }
}