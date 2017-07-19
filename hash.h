#ifndef HASH_H
#define HASH_H
#include <stdlib.h>
#include <string>
using namespace std;
class Hash{
public:
  Hash(string);
  int key;
  int hash() const;  //return the hash value
};
#endif
