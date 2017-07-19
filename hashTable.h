#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hash.h"
#include "link.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
class Link;
class HashTable{
public:
  HashTable();
  ~HashTable();

  HashTable& add(string str, string d);

  bool inTable(string)const;

  const string operator[](const string str) const;

private:
  int size;   //the size of the array table
  Link **table;  //dynamically allocated array of pointers, each
		 //pointer pointing to a linked list of Links or NULL

  // return true if and only iff k is a positive prime
  //bool prime(int k);

  // if b is true do nothing, else display on cerr the error message and exit
  static void check(bool b, const char *mess);
};

#endif
