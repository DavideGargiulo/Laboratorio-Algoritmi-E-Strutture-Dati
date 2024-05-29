// lasd::HashTableOpnAdr<int> ht(3);
//   ht.Insert(10);
//   ht.Insert(20);
//   ht.Insert(30);
//   Size(loctestnum, loctesterr, ht, true, 3);

//   Check existence of the inserted elements
//   Exists(loctestnum, loctesterr, ht, true, 10);
//   Exists(loctestnum, loctesterr, ht, true, 20);
//   Exists(loctestnum, loctesterr, ht, true, 30);

//   Removing one element and check existence
//   Remove(loctestnum, loctesterr, ht, 20);
//   Exists(loctestnum, loctesterr, ht, false, 20);
//   Size(loctestnum, loctesterr, ht, true, 2);

//   Inserting another element to cause collision
//   ht.Insert(40);
//   Size(loctestnum, loctesterr, ht, true, 3);

//   Check existence of the new set of elements
//   Exists(loctestnum, loctesterr, ht, true, 10);
//   Exists(loctestnum, loctesterr, ht, true, 30);
//   Exists(loctestnum, loctesterr, ht, true, 40);
//   ht.Clear();

//   lasd::Vector<int> vec1(127);
//   for (uint i = 0; i < 127; i++) {
//     vec1[i] = pow(-2, i % 24) * ((61 * i + 29) % 127);
//   }
//   cout <<"Edge case with size 1" << endl;
//   lasd::HashTableOpnAdr<int> ht2(1, vec1);
//   for (int i = 0; i < 127; i += 17) {
//     Exists(loctestnum, loctesterr, ht2, true, vec1[i]);   
//   }

//   for (int i = 0; i < 127; i++) {
//     ht2.Insert(vec1[i]);
//   }

//   for (int i = 0; i < 127; i += 17) {
//     Exists(loctestnum, loctesterr, ht2, true, vec1[i]);
//   }

//   for (int i = 0; i < 127; i += 17) {
//     ht2.Remove(vec1[i]);
//     Exists(loctestnum, loctesterr, ht2, false, vec1[i]);
//   }

//   Empty(loctestnum, loctesterr, ht, true);
//   Size(loctestnum, loctesterr, ht, true, 0);

//   lasd::HashTableOpnAdr<int> ht3(ht2);
//   EqualHT(loctestnum, loctesterr, ht3, ht2);
//   lasd::HashTableOpnAdr<int> ht4(move(ht3));
//   NonEqualHT(loctestnum, loctesterr, ht3, ht4);
//   ht3 = ht4;
//   EqualHT(loctestnum, loctesterr, ht3, ht4);

#include <iostream>
#include <limits>
#include <cmath>

#include "../../zlasdtest/container/container.hpp"
#include "../../zlasdtest/container/testable.hpp"
#include "../../zlasdtest/container/dictionary.hpp"
#include "../../zlasdtest/container/linear.hpp"

#include "../../zlasdtest/vector/vector.hpp"

#include "../../zlasdtest/list/list.hpp"

#include "../../zlasdtest/hashtable/hashtable.hpp"

#include "../../container/container.hpp"
#include "../../container/testable.hpp"
#include "../../container/dictionary.hpp"
#include "../../container/linear.hpp"

#include "../../vector/vector.hpp"

#include "../../list/list.hpp"

#include "../../hashtable/hashtable.hpp"
#include "../../hashtable/clsadr/htclsadr.hpp"
#include "../../hashtable/opnadr/htopnadr.hpp"

using namespace std;

void MyHashTableInt(lasd::HashTable<int> & ht, const lasd::LinearContainer<int> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    // Collision Handling
    int colliding_values[] = {5, 5 + 83, 5 + 2 * 83}; // Assuming hash table initial size of 83
    for (const auto &val : colliding_values) {
      InsertC(loctestnum, loctesterr, ht, val);
    }
    for (const auto &val : colliding_values) {
      Exists(loctestnum, loctesterr, ht, true, val);
    }

    // Deletion of Non-existent Element
    int non_existent = -999;
    Remove(loctestnum, loctesterr, ht, non_existent);
    Exists(loctestnum, loctesterr, ht, false, non_existent);

    // Load Factor Handling
    int initial_capacity = 83;
    ht.Resize(initial_capacity);
    Size(loctestnum, loctesterr, ht, true, 128);
    for (int i = 0; i < 100; ++i) {
      InsertC(loctestnum, loctesterr, ht, i);
    }
    Size(loctestnum, loctesterr, ht, true, 221);

    // Boundary Values
    int min_int = std::numeric_limits<int>::min();
    int max_int = std::numeric_limits<int>::max();
    InsertC(loctestnum, loctesterr, ht, min_int);
    InsertC(loctestnum, loctesterr, ht, max_int);
    Exists(loctestnum, loctesterr, ht, true, min_int);
    Exists(loctestnum, loctesterr, ht, true, max_int);

    // Empty Insertion/Removal
    ht.Clear();
    Remove(loctestnum, loctesterr, ht, 0);
    Size(loctestnum, loctesterr, ht, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void MyHashTableInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<int> Test" << endl;
  try {
    lasd::Vector<int> vec(127);
    for (uint i = 0; i < 127; i++) {
      vec[i] = pow(-2, i % 24) * ((61 * i + 29) % 127);
    }

    lasd::HashTableOpnAdr<int> htopnadr(83, vec);
    cout << endl << "Begin of HashTableOpnAdr<int> Test:" << endl;
    MyHashTableInt(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableOpnAdr<int> cophtopnadr(htopnadr);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    InsertC(loctestnum, loctesterr, cophtopnadr, 100);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myTestHashTable(uint & testnum, uint & testerr) {
  MyHashTableInt(testnum, testerr);
  std::cout << std::endl << "My HashTable Tests (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}