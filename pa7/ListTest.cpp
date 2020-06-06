//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){


   List A, B, C, D, E;

   A.insertBefore(1);
   A.insertBefore(2);
   A.insertBefore(2);
   A.insertBefore(1);
   A.insertBefore(2);
   A.insertBefore(3);
   A.insertBefore(1);
   A.findPrev(3);
   A.cleanup();



   B.insertBefore(1);
   B.insertBefore(2);
   B.insertBefore(2);
   B.insertBefore(1);
   B.insertBefore(2);
   B.insertBefore(3);
   B.insertBefore(1);
   B.findPrev(3);
   B.movePrev();
   B.cleanup();

   
   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;

   A.moveBack();
   B.moveBack();
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;

   A.clear();
   B.clear();


   for (int i = 0 ; i < 16; i++){
      D.insertBefore(i);
   }
   cout << "D = " << D << endl;

   D.moveFront();
   List X, Y, Z;
   for (int i = 0; i < (D.size()/2); i++){
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
   cout << "Z = " << Z << endl;
   cout << "D==Z is " << (D==Z?"true":"false") << endl;
   D = Z;
   cout << "D = " << D << endl;
   cout << "D==Z is " << (D==Z?"true":"false") << endl;
   D.moveFront();

   
   cout << "D ( Next 17)" ;

   printf("%d\n", D.findNext(17));

   D.cleanup();
   cout << "D = " << D << endl;
   cout << D.position() << endl;

   D.clear();


   return(0);
}
