/*********************************************************************************
* Yuehao Li, yli509
* 2020 Spring CSE101 PA7
* List.cpp
* List ADT for PA7
*********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

List::Node::Node(int x){
   data = x;
   next = nullptr;
   prev = nullptr;

}

List::List(){
   frontDummy = nullptr;
   backDummy = nullptr;
   beforeCursor = nullptr;
   afterCursor = nullptr;
   pos_cursor = 0;
   num_elements = 0;
}

List::List(const List& L){
   // make this an empty Queue
   frontDummy = nullptr;
   backDummy = nullptr;
   beforeCursor = nullptr;
   afterCursor = nullptr;
   pos_cursor = 0;
   num_elements = 0;

   // load elements of Q into this
   Node* N = L.frontDummy;
   while( N!=nullptr ){
      this->insertBefore(N->data);
      N = N->next;
   }
   pos_cursor = 0;
}

List::~List(){
    while( num_elements>0 ){
        clear();
    }
}

bool List::isEmpty(){
    if (num_elements == 0){
        return true;
    }
    else{
        return false;
    }

}

int List::size(){
    return(num_elements);
}

int List::position(){
    return (pos_cursor);
}

void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = nullptr;
    afterCursor = frontDummy;
}


void List::moveBack(){
    
    pos_cursor = size();
    afterCursor = nullptr;
    beforeCursor = backDummy;
}

int List::peekNext(){
    if(position()>=size()){
        cerr <<"List ERROR: Calling peekNext() with cursor at last."<< endl;
        exit(EXIT_FAILURE);
    }
    return afterCursor->data;
}

int List::peekPrev(){
    if(position()<=0){
        cerr <<"List ERROR: Calling peekPrev() with cursor at front." << endl;
        exit(EXIT_FAILURE);
    }
    return beforeCursor->data;
}  

int List::moveNext(){
    if(position()>=size()){
        cerr << "List ERROR: Calling moveNext() with cursor at last."<< endl;
        exit(EXIT_FAILURE);
    }
    int result = afterCursor->data;
    pos_cursor++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    return result;
}

int List::movePrev(){
    if(position()<=0){
        cerr <<"List ERROR: Calling movePrev() with cursor at front."<< endl;
        exit(EXIT_FAILURE);
    }
    int result = beforeCursor->data;
    pos_cursor--;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    return result;
}

void List::insertAfter(int x){
    Node* N = new Node(x);
    if (num_elements == 0){
        frontDummy = backDummy = N;
        afterCursor = N;
    }
    else if (pos_cursor == size()){
        backDummy->next = N;
        N->prev = backDummy;
        backDummy = N;
        afterCursor = N;
    }
    else if (pos_cursor == 0){
        N->next = frontDummy;
        frontDummy->prev = N;
        afterCursor = N;
        frontDummy = N;
    }
    else{
        afterCursor ->prev = N;
        N->next = afterCursor;
        N->prev = beforeCursor;
        beforeCursor->next = N;
        afterCursor = N;
    }
    num_elements++;
}

void List:: insertBefore(int x){
    Node* N = new Node(x);
    if (size() == 0){
        frontDummy = backDummy = N;
        beforeCursor = N;
    }
    else if (pos_cursor == 0){
        N->next = frontDummy;
        frontDummy->prev = N;
        beforeCursor = N;
        frontDummy = N;
    }
    else if (pos_cursor == size()){
        N->prev = backDummy;
        backDummy->next = N;
        beforeCursor = N;
        backDummy = N;
    }
    else{
        N->next = afterCursor;
        N->prev = beforeCursor;
        afterCursor->prev = N;
        beforeCursor->next = N;
        beforeCursor = N;
    }
    pos_cursor++;
    num_elements++;
}

void List::eraseAfter(){
    if (position() >= size()){
        cerr << "List ERROR: Calling eraseAfter() with cursor at last." << endl;
        exit(EXIT_FAILURE);
    }
    Node * N;
    if (size() == 1){
        N = frontDummy;
        frontDummy = backDummy = beforeCursor = afterCursor = nullptr;
    }
    else if (pos_cursor == 0){
        N = frontDummy;
        afterCursor = N->next;
        afterCursor->prev = nullptr;
        frontDummy = afterCursor;
    }
    else if (pos_cursor == size() - 1){
        N = afterCursor;
        afterCursor = nullptr;
        beforeCursor->next = nullptr;
        backDummy = beforeCursor;
    }
    else{
        N = afterCursor;
        N ->next->prev = beforeCursor;
        beforeCursor->next = N->next;
        afterCursor = N->next;
    }
    delete N;
    num_elements--;
}

void List:: eraseBefore(){
    if (position() <= 0){
        cerr <<"List ERROR: Calling eraseAfter() with cursor at last.\n" << endl;
        exit(EXIT_FAILURE);
    }
    Node* N;
    if (size() == 1){
        N = frontDummy;
        frontDummy = backDummy = beforeCursor = afterCursor = nullptr;
    }
    else if ( pos_cursor == size()){              // At the end.
        N = backDummy;
        beforeCursor = N->prev;
        N->prev->next = nullptr;
        backDummy = N->prev;
    }
    else if (pos_cursor == 1){
        N = beforeCursor;
        beforeCursor = nullptr;
        frontDummy = afterCursor;
        afterCursor->prev = nullptr;

    }
    else{
        N = beforeCursor;
        afterCursor->prev = N->prev;
        N->prev->next = afterCursor;
        beforeCursor = N->prev;
    }
    pos_cursor--;
    num_elements--;
    delete N;
}


int List::findNext(int x){
    Node * N ;
    while(position() != size()){
        N = afterCursor;
        if (N->data == x){
            moveNext();
            return position();
        }
        moveNext();
    }
    return -1;
}

int List ::findPrev(int x){
    Node* N;
    while (position() != 0){
        N = beforeCursor;
        if (N->data == x){
            movePrev();
            return position();
        }
        movePrev();
    }
    return -1;
}

void List :: cleanup(){
    Node* tempBefore = beforeCursor;
    Node* tempAfter = afterCursor;
    int * array = new int[num_elements];
    for (int i = 0; i < num_elements; i++)
        array[i] = 0;
    //int array[num_elements];
    int cursor = pos_cursor;
    int index = 0;
    //Node * N = frontDummy;
    int temp;
    moveFront();
    bool check = false;
    while(pos_cursor != size()){
        check = false;
        for(int i = 0; i < index; i++ ){
            temp = afterCursor->data;
            if (afterCursor->data == array[i]){
                if (pos_cursor < cursor){
                    //count ++;
                    cursor--;
                }
                if (afterCursor == tempBefore){
                    tempBefore = tempBefore->prev;
                }
                else if (afterCursor == tempAfter){
                    tempAfter = tempAfter->next;
                }
                
                check = true;
                break;
            }
        }
        if (check == true )
            eraseAfter();
        else 
            moveNext();
        array[index] = temp;
        index++;
        
    }

    pos_cursor = cursor ;
    beforeCursor = tempBefore;
    afterCursor = tempAfter;
    delete [] array;
}

void List::clear(){
    moveFront();
    while(size() != 0){
        eraseAfter();
    }
}


List List::concat(const List& L){
    List J;
    Node* N = this->frontDummy;
    Node* M = L.frontDummy;
    while(N != nullptr){
        J.insertBefore(N->data);
        N = N->next;
    }
    while(M!=nullptr){
        J.insertBefore(M->data);
        M = M->next;
    }
    moveFront();
    return J;
}

string List::to_string(){
    int i = 1;
    Node * N = nullptr;
    string s = "";
    s += "(";
    for (N = frontDummy; N!=nullptr; N = N->next){
        if (i == 1){
           s += std::to_string(N->data); 
           i++;
        }
        else{
            s +="," + std::to_string(N->data)  ;
        }
        
    }
    s += ")";
    return s;
}

bool List::equals(const List& R){
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;
    eq = ( this->num_elements == R.num_elements);
    N = this->frontDummy;
    M = R.frontDummy;
    while (eq && N!=nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

ostream& operator<<( std::ostream& stream, List& L ){
    return stream << L.List::to_string();
}

bool operator==( List& A, const List& B ){
    return A.List::equals(B);
}

List& List::operator=( const List& L ){
    if (this != &L){
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
    }

    return *this;
}