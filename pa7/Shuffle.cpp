/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA7
* Shuffle.cpp
* Main function for PA7
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include"List.h"


void shuffle(List& D){
    int i = 0;
    D.moveFront();
    List X, Y, Z;
    for (i = 0; i < (D.size()/2); i++){
        X.insertBefore(D.peekNext());
        D.moveNext();
    }
    for (int j = D.size()/2 ; j < D.size(); j++){
        Y.insertBefore(D.peekNext());
        D.moveNext();
    }
    X.moveFront();
    Y.moveFront();
    while(Z.size() != D.size()){
        if (Y.position() != Y.size()){
            Z.insertBefore(Y.peekNext());
            Y.moveNext();
        }
        if (X.position() != X.size()){
            Z.insertBefore(X.peekNext());
            X.moveNext();
        }
    }
    D = Z;
}

int main(int argc, char * argv[]){

    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << "  <number>" << endl;
        return(EXIT_FAILURE);
    }
    /*if (isdigit(argv[1]) == 0){
        cerr << "Usage: " << argv[0] << "<number>" << endl;
        return(EXIT_FAILURE);
    }*/
    int number = atoi(argv[1]);

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    List A, B;
    int count;
    for (int i = 0; i<number; i++){
        int deck = i + 1;
        count = 0;
        for (int x = 0; x < deck ; x++){
            A.insertBefore(x);
            B.insertBefore(x);
        }

        shuffle(A);
        count++;
        while(A.equals(B) != true){
            shuffle(A);
            count ++;
        }
        printf("%d               %d\n", i + 1, count);       // print result. 

        A.clear();                               // A to empty state.
        B.clear();                                // B to empty state.
    }

    return (EXIT_SUCCESS);
}