#include <iostream>

#include "../zmytest/myVector/myVector.hpp"
#include "../zmytest/myHashtable/myHashtable.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void mytest() {
  unsigned loctestnum = 0, loctesterr = 0;

  cout << "Begin of Vector tests" << endl;
  myTestVector(loctestnum, loctesterr);

  cout << "Begin of My HashTable tests" << endl;
  myTestHashTable(loctestnum, loctesterr);

  cout << endl << "My Test " << ((loctesterr == 0) ? "0 errors" : to_string(loctesterr) + " errors") << " out of " << loctestnum << " tests" << endl;
}