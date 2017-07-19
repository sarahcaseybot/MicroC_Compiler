/*J Femister
  CSE 109 - 010
  Fall 2015
*/

#ifndef STACK_H
#define STACK_H

#include <iostream>
//#include "hash.h"
#include "hashTable.h"
using namespace std;
class HashTable;
/* 
   A simple implementation of a stack for ints.
*/

// This is a comment

class Stack {
public:
  // Constructors
  Stack(int n);
   Stack(); // Default constructor
  Stack(const Stack&); // Copy Constructor - deep copy

  // Destructor
  ~Stack();

  // Regular Member Functions
  void push(HashTable* val);
  HashTable* pop();
  HashTable* peek() const;
  int count();
  // Inline Member Function
  //  bool isEmpty() const { return tos == EMPTY; } // inline member function

  // Overloaded Operator Friend Functions
  // friend ostream& operator <<(ostream& out, const Stack& s);

  // Overloaded Operator Member Functions
  // const int& operator [](int i) const; // rvalue

  HashTable* operator [](int i); // lvalue
  
private:
  HashTable** stack;
  int size;
  int tos;
  static const int EMPTY = -1;
  void checkIndex(int i) const;
};

#endif

