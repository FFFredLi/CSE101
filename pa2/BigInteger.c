#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BigInteger.h"
#include "List.h"

#define POWER 9
#define BASE 1000000000

typedef struct BigIntegerObj{
    int sign;
    List number;
}BigIntegerObj;


BigInteger newBigInteger(){
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->sign = 0;
    B->number = newList();
    return B;
}


// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    if(pN != NULL && *pN != NULL){
        freeList(&(*pN)->number);
        
        // Code...

        free(*pN);
        *pN = NULL; 
    }

    
}


// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
    if (N == NULL ){
        printf("BigInteger Error : Calling sign() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }

    if(N->sign == 0){
        return 0;
    }
    if(N->sign == -1){
        return -1;
    }
    if(N->sign == 1){
        return 1;
    }
}


// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
    if (A == NULL || B == NULL){
        printf("BigInteger Error : Calling compare() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    if(sign(A) > sign(B)){                 // A: +          B: -
        return 1;
    }
    else if (sign(A) < sign(B)){          // A: -          B: +
        return -1;
    }
    else{                                 // A: +          B: + ;              A: -         B: -
        if (sign(A) == 1){
            if (length(A->number) > length(B->number))          // A: 1234567        B: 123
                return 1;
            else if(length(B->number) > length(A->number))          // A: 123            B: 1234567
                return -1;
            else{                                                   // A: 123456         B: 654321
                moveFront(A->number);
                moveFront(B->number);
                while (index(A->number) != -1){
                    if(get(A->number) > get(B->number))
                        return 1;
                    else if (get(A->number) < get(B->number))
                        return -1;
                    moveNext(A->number);                          // Cursor Next;
                    moveNext(B->number);
                }
            }
        }
        else if (sign(A) == -1){
            if (length(A->number) > length(B->number))          // A: -1234567        B: -123
                return -1;
            else if(length(B->number) > length(A->number))          // A: -123            B: -1234567
                return 1;
            else{                                                   // A: -123456         B: -654321
                moveFront(A->number);
                moveFront(B->number);
                while (index(A->number) != -1){
                    if(get(A->number) > get(B->number))
                        return -1;
                    else if (get(A->number) < get(B->number))
                        return 1;
                    moveNext(A->number);                          // Cursor Next;
                    moveNext(B->number);
                }
            }
        }
        return 0;
    }

}


// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
    if (A == NULL || B == NULL){
        printf("BigInteger Error : Calling equals() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    if (A->sign != B->sign){
        return 0;
    }
    if(length(A->number) != length(B->number)){
        return 0;
    }

    moveFront(A->number);
    moveFront(B->number);
    int i = 1;
    while(index(A->number) != -1 && index(B->number)!= -1){
        if(get(A->number) != get(B->number)){
            i = 0;
        }
        moveNext(A->number);
        moveNext(B->number);
    }
    return i;
}


// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
    N->sign = 0;
    clear(N->number);
}


// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
    if (N == NULL){
        printf("BigInteger Error : Calling negate() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    if(N->sign == 1){
        N->sign = -1;
    }
    else if(N->sign == -1){
        N->sign = 1;
    }
    
}


void putInt(BigInteger B, char* s, int state){
    int length = strlen(s) - 1;
    char temp[POWER]; 
    char * endptr;
    long num;
    if (state == 1){                              // with {+, -} prefix ::   + 12345 -13532
        while (length > 1){
            for (int i = POWER - 1; i > -1; i--){
                if (length == 0){
                    temp[i] = '0';
                }
                else{
                    temp[i] = s[length];
                    length--;
                }
                
            }
            num = strtol(temp, &endptr, 10);
            if (num == 0 && length == 0)
                continue;
            prepend(B->number, num);
        }
        
    }
    else{                                         // without {+, -} prefix     23042
        while (length >= 0){
            for (int i = POWER - 1; i > -1; i--){
                if (length < 0){
                    temp[i] = '0';
                    length--;
                }
                else{
                    temp[i] = s[length];
                    length--;
                }
                
            }
            num = strtol(temp, &endptr, 10);
            if (num == 0 && length == 0)
                continue;
            prepend(B->number, num);
            
        }
        
    }
}


// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.

BigInteger stringToBigInteger(char* s){
    if (s[0] == '+' || s[0] == '-' || isdigit(s[0]) > 0){
        for (int i = 1; i < strlen(s); i++){
            if (isdigit(s[i]) == 0){                 // 
                printf("BigInteger Error: Calling stringToBigInteger() with non-digits arguments\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else{
        printf("BigInteger Error: Calling stringToBigInteger() with non-digits arguments\n");
        exit(EXIT_FAILURE);
    }
    
    
    BigInteger B = newBigInteger();
    if(s[0] == '-'){
        B->sign = -1;
        putInt(B, s, 1);
    }
    else if (s[0] == '+'){
        B->sign = 1;
        putInt(B, s, 1);
    }
    else {
        B->sign = 1;
        putInt(B, s, 0);
    }
        
    return B;
}


// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
    if (N == NULL){
        printf("BigInteger Error : Calling copy() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }

    BigInteger C = newBigInteger();
    C->sign = N->sign;
    C->number = copyList(N->number);
    return C;
    
}


// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
    if (A == NULL || B == NULL || S == NULL){
        printf("BigInteger Error : Calling add() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    makeZero(S);
    moveBack(A->number);
    moveBack(B->number);

    List N = A->number;
    List M = B->number;
    List Q = S->number;
    long carry = 0;
    long temp;
    negate(B);
    int result = compare(A, B);
    negate(B);
    if (result == 0){
        makeZero(S);
        return;
    }
    if (sign(A) == sign(B)){                                    // 1 + 1 = 2 ;    -1 + (-1) = -2;
        while (index(N) != -1 || index(M) != -1){                 //   +1   +    +2
            if(index(N) == -1){
                temp = get(M) + carry;
                movePrev(M);
            }
            else if(index(M) == -1){
                temp = get(N) + carry;
                movePrev(N);
            }
            else{
                temp = get(N) + get(M) + carry;
                movePrev(N);
                movePrev(M);
            }
            
            if (temp >= BASE){
                prepend(Q, temp - BASE);
                carry = 1;
            } 
            else{
                prepend(Q, temp);
                carry = 0;
            }   
        }
        if (carry == 1)                           // 50 + 50 = 1  00
            prepend(Q, carry);
        
        S -> sign = A ->sign;
    }
    else if (sign(A) == 1 && sign(B) == -1){ // 1+(-1)  ; 
        if (result == -1)
            S->sign = -1;
        else 
            S->sign = 1;
        while(index(N) != -1 || index(M) != -1){
            
            if(index(N) == -1){
                if(result == -1)
                    temp = get(M) + carry;
                else
                    temp = -(get(M)) + carry;
                movePrev(M);
            }
            else if(index(M) == -1){
                if (result == -1)
                    temp = -get(N) + carry;   
                else
                    temp = get(N) + carry;         // B>A   B length < A       XXXX
                movePrev(N);
            }
            else{
                if (result == -1)
                    temp = get(M) - get(N) + carry;
                else
                    temp = get(N) - get(M) + carry;
                movePrev(N);
                movePrev(M);
            }

            if (temp < 0){
                prepend(Q, temp + BASE);
                carry = -1;
            }
            else{
                prepend(Q, temp);
                carry = 0;
            }
        }
    }
    else if (sign(A) == -1 && sign(B) == 1){    //-1 + 1;
        if (result == -1)
            S->sign = -1;
        else
            S->sign = 1;
        while(index(N) != -1 || index(M) != -1){
            
            
            if (index(N) == -1){
                if(result == -1)
                    temp = -(get(M)) + carry;
                else
                    temp = get(M) + carry;
                movePrev(M);
            }
            else if (index(M) == -1){
                if (result == -1)
                    temp = get(N) + carry;
                else 
                    temp = -(get(N))+carry;
                movePrev(N);
            }
            else{
                if (result == -1)
                    temp = get(M) - get(N) + carry;
                else 
                    temp = get(N) - get(M) + carry;
                movePrev(N);
                movePrev(M);
            }

            if (temp < 0){
                prepend(Q, temp + BASE);
                carry = -1;
            }
            else{
                prepend(Q, temp);
                carry = 0;
            }
        }
    }                                             

    // S = A + B

    
}


// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    if (A == NULL || B == NULL){
        printf("BigInteger Error : Calling sum() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }

    moveBack(A->number);
    moveBack(B->number);
    BigInteger new = newBigInteger();

    
    
    add(new , A, B);
    return new;
}


// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
    if (A == NULL || B == NULL || D == NULL){
        printf("BigInteger Error : Calling subtract() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    makeZero(D);
    moveBack(A->number);
    moveBack(B->number);
    
    List N = A->number;
    List M = B->number;
    List Q = D->number;
    long carry = 0;
    long temp;
    int result = compare(A, B);
    
    // D = A - B

    if (result == 0){
        makeZero(D);
        return;
    } 
    
    if (sign(A) == 1 && sign(B) == 1){
        if (result == -1)
            D->sign = -1;
        else 
            D->sign = 1;
        while(index(N) != -1 || index(M) != -1){
            
            if(index(N) == -1){
                if(result == -1)
                    temp = get(M) + carry;
                else
                    temp = -(get(M)) + carry;
                movePrev(M);
            }
            else if(index(M) == -1){
                if (result == -1)
                    temp = -get(N) + carry;   
                else
                    temp = get(N) + carry;         // B>A   B length < A       XXXX
                movePrev(N);
            }
            else{
                if (result == -1)
                    temp = get(M) - get(N) + carry;
                else
                    temp = get(N) - get(M) + carry;
                movePrev(N);
                movePrev(M);
            }

            if (temp < 0){
                prepend(Q, temp + BASE);
                carry = -1;
            }
            else{
                prepend(Q, temp);
                carry = 0;
            }
        }
    }
    else if (sign(A) != sign(B)){
        D->sign = A->sign;

        while (index(N) != -1 || index(M) != -1){                 //   +1   +    +2
            if(index(N) == -1){
                temp = get(M) + carry;
                movePrev(M);
            }
            else if(index(M) == -1){
                temp = get(N) + carry;
                movePrev(N);
            }
            else{
                temp = get(N) + get(M) + carry;
                movePrev(N);
                movePrev(M);
            }
            
            if (temp >= BASE){
                prepend(Q, temp - BASE);
                carry = 1;
            } 
            else{
                prepend(Q, temp);
                carry = 0;
            }   
        }
        if (carry == 1)                           // 50 + 50 = 1  00
            prepend(Q, carry);
    }
    else if (sign (A) == -1 && sign(B) == -1){
        if (result == 1)
            D->sign = 1;
        else
            D->sign = -1;
        while(index(N) != -1 || index(M) != -1){
            if(index(N) == -1){
                if(result == -1)
                    temp = -(get(M)) + carry;
                else
                    temp = get(M) + carry;
                movePrev(M);
            }
            else if (index(M) == -1){
                if(result == -1)
                    temp = get(N) + carry;
                else 
                    temp = -(get(N))+ carry;
                movePrev(N);
            }
            else{
                if (result == -1)
                    temp = get(N) - get(M) +carry;
                else
                    temp = get(M) - get(N) + carry;
                movePrev(M);
                movePrev(N);
            }

            if (temp < 0){
                prepend(Q, temp + BASE);
                carry = -1;
            }
            else{
                prepend(Q, temp);
                carry = 0;
            }

        }

        
    }

    
}


// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
    if (A == NULL || B == NULL){
        printf("BigInteger Error : Calling diff() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    BigInteger dif = newBigInteger();

    subtract(dif, A, B);
    return dif;
}


long exponent(int count){
    long result = 1;
    if (count == 0)
        return result;
    else{
        while(count != 0){
            result *= BASE;
            --count;
        }
    }
    return result;
}


// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
    if (A == NULL || B == NULL || P == NULL){
        printf("BigInteger Error : Calling multiply() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }

    if(P != A && P!= B){
        makeZero(P);
        moveBack(A->number);
        moveBack(B->number);
    }
    
    long temp;
    int counterA = 0;
    int counterB = 0;
    long carry = 0;
    long ind;
    if (sign(A) == sign(B))
        P->sign = 1;
    else
        P->sign = -1;
    
    while (index(B->number) != -1){
        counterA = 0;
        moveBack(A->number);
        
            while(index(A->number)!= -1){
                for (int i = 0 ; i < POWER ; i++){
                    long t = get(B->number);
                    long ind = t%exponent(i+1);
                    temp += ind * exponent(i)*get(A->number)*exponent(counterA) + carry;
                    carry = temp / BASE;
                    prepend(P->number, temp%BASE);
                    t = t - ind;
                }
                    
                

                movePrev(A->number);
                counterA++;
            }
            
        


        while (index(A->number) != -1){
            
            moveBack(P->number);

            temp = get(B->number) * exponent(counterB) * get(A->number) * exponent(counterA); 

            if (counterB == 0 && counterA == 0){
                append(P->number, temp%BASE);
            }
            else{
                set(P->number, temp%BASE);
            }
            

            carry = temp / BASE;

            movePrev(A->number);
            counterA++;
        }
        movePrev(B->number);
        counterB++;

    }



    // P = A * B

}


// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
    if (A == NULL || B == NULL){
        printf("BigInteger Error : Calling prod() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    BigInteger product = newBigInteger();
    multiply(product, A, B);
    return product;
}


// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
    if (N == NULL){
        printf("BigInteger Error : Calling printBigInteger() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }

    if(N->sign == -1)
        fprintf(out,"-");
    else if(N->sign == 0){
        fprintf(out,"0\n");
        return;
    }
        

    printList(out, N->number);
}


void numMulti (BigInteger B, long x){
    if (B == NULL){
        printf("BigInteger Error : Calling numMulti() on NULL BigInteger reference.");
        exit(EXIT_FAILURE);
    }
    long temp;
    long carry;

    moveBack(B->number);
    while(index(B->number) != -1){
        temp = x * get(B->number)+carry;
        carry = temp / BASE;
        temp = temp % BASE;
        set(B->number, temp);
    }
}