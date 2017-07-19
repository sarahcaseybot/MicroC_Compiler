#include "hash.h"
#include <string>
Hash::Hash(string str) {
  int tmp = 0;
  string p = str;

  for(unsigned i = 0; i < p.length(); i++) {
    tmp += p[i];
  }
  
  key = abs(tmp);
}

int Hash::hash() const{
  return key;
}
