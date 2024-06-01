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
    int collidingValues[] = {7, 7 + 89, 7 + 2 * 89};
    for (const auto &val : collidingValues) {
      InsertC(loctestnum, loctesterr, ht, val);
    }
    for (const auto &val : collidingValues) {
      Exists(loctestnum, loctesterr, ht, true, val);
    }

    int non_existent = -888;
    Remove(loctestnum, loctesterr, ht, non_existent);
    Exists(loctestnum, loctesterr, ht, false, non_existent);

    int initial_capacity = 89;
    ht.Resize(initial_capacity);
    Size(loctestnum, loctesterr, ht, true, 133);
    for (int i = 0; i < 105; ++i) {
      InsertC(loctestnum, loctesterr, ht, i);
    }
    Size(loctestnum, loctesterr, ht, true, 228);

    int min_int = std::numeric_limits<int>::min();
    int max_int = std::numeric_limits<int>::max();
    InsertC(loctestnum, loctesterr, ht, min_int);
    InsertC(loctestnum, loctesterr, ht, max_int);
    Exists(loctestnum, loctesterr, ht, true, min_int);
    Exists(loctestnum, loctesterr, ht, true, max_int);

    ht.Clear();
    Remove(loctestnum, loctesterr, ht, 0);
    Size(loctestnum, loctesterr, ht, true, 0);

    ht.Clear();
    InsertC(loctestnum, loctesterr, ht, 48);
    InsertC(loctestnum, loctesterr, ht, 48);

    Remove(loctestnum, loctesterr, ht, 1000);

    Exists(loctestnum, loctesterr, ht, true, 48);

    ht.Clear();
    Remove(loctestnum, loctesterr, ht, 48);
    Exists(loctestnum, loctesterr, ht, false, 48);

    ht.Clear();
    Exists(loctestnum, loctesterr, ht, false, 2);

    InsertC(loctestnum, loctesterr, ht, 2);
    Size(loctestnum, loctesterr, ht, true, 1);
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
    lasd::Vector<int> vec(131);
    for (uint i = 0; i < 131; i++) {
      vec[i] = pow(-2, i % 25) * ((67 * i + 31) % 131);
    }

    lasd::HashTableOpnAdr<int> htopnadr(89, vec);
    cout << endl << "Begin of My HashTableOpnAdr<int> Test:" << endl;
    MyHashTableInt(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";
    lasd::HashTableClsAdr<int> htclsadr(89, vec);
    cout << endl << "Begin of My HashTableClsAdr<int> Test:" << endl;
    MyHashTableInt(htclsadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableOpnAdr<int> cophtopnadr(htopnadr);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    InsertC(loctestnum, loctesterr, cophtopnadr, 110);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);

    lasd::HashTableClsAdr<int> cophtclsadr(htclsadr);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    InsertC(loctestnum, loctesterr, cophtclsadr, 110);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void MyHashTableDouble(lasd::HashTable<double> & ht, const lasd::LinearContainer<double> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    double values[] = {1.5, -3.7, 22.1, -45.9};
    for (const auto &val : values) {
      InsertC(loctestnum, loctesterr, ht, val);
    }
    for (const auto &val : values) {
      Exists(loctestnum, loctesterr, ht, true, val);
    }

    Remove(loctestnum, loctesterr, ht, -3.7);
    Exists(loctestnum, loctesterr, ht, false, -3.7);

    double small_large_values[] = {std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
    for (const auto &val : small_large_values) {
      InsertC(loctestnum, loctesterr, ht, val);
    }
    for (const auto &val : small_large_values) {
      Exists(loctestnum, loctesterr, ht, true, val);
    }

    double precise_values[] = {0.123456789, -0.987654321};
    for (const auto &val : precise_values) {
      InsertC(loctestnum, loctesterr, ht, val);
    }
    for (const auto &val : precise_values) {
      Exists(loctestnum, loctesterr, ht, true, val);
    }

    ht.Clear();
    Size(loctestnum, loctesterr, ht, true, 0);
    InsertC(loctestnum, loctesterr, ht, 42.42);
    Exists(loctestnum, loctesterr, ht, true, 42.42);

    for (int i = 0; i < 10; ++i) {
      InsertC(loctestnum, loctesterr, ht, i * 1.1);
    }
    for (int i = 0; i < 10; ++i) {
      Exists(loctestnum, loctesterr, ht, true, i * 1.1);
    }

    for (int i = 0; i < 10; ++i) {
      Remove(loctestnum, loctesterr, ht, i * 1.1);
      Exists(loctestnum, loctesterr, ht, false, i * 1.1);
    }
    Size(loctestnum, loctesterr, ht, true, 1);

  } catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void MyHashTableDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<double> Test" << endl;
  try {
    lasd::Vector<double> vec(101);
    for (uint i = 0; i < 101; i++) {
      vec[i] = pow(-1.5, i % 20) * ((73.2 * i + 41.3) / 101.0);
    }

    lasd::HashTableOpnAdr<double> htopnadr(101, vec);
    cout << endl << "Begin of My HashTableOpnAdr<double> Test:" << endl;
    MyHashTableDouble(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";
    lasd::HashTableClsAdr<double> htclsadr(101, vec);
    cout << endl << "Begin of My HashTableClsAdr<double> Test:" << endl;
    MyHashTableDouble(htclsadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableOpnAdr<double> cophtopnadr(htopnadr);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    InsertC(loctestnum, loctesterr, cophtopnadr, 100.1);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);

    lasd::HashTableClsAdr<double> cophtclsadr(htclsadr);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    InsertC(loctestnum, loctesterr, cophtclsadr, 110.11);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
  } catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void MyHashTableString(lasd::HashTable<string> & ht, const lasd::LinearContainer<string> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    string values[] = {"alpha", "bravo", "charlie", "delta", "echo", "foxtrot"};
    for (const auto &val : values) {
      InsertC(loctestnum, loctesterr, ht, val);
    }
    for (const auto &val : values) {
      Exists(loctestnum, loctesterr, ht, true, val);
    }

    Remove(loctestnum, loctesterr, ht, string("charlie"));
    Exists(loctestnum, loctesterr, ht, false, string("charlie"));
    Size(loctestnum, loctesterr, ht, true, 119);

    string special_chars[] = {"!@#", "$%^", "&*()", "-_=+", "`~"};
    for (const auto &val : special_chars) {
      InsertC(loctestnum, loctesterr, ht, val);
    }
    for (const auto &val : special_chars) {
      Exists(loctestnum, loctesterr, ht, true, val);
    }

    InsertC(loctestnum, loctesterr, ht, string(""));
    Exists(loctestnum, loctesterr, ht, true, string(""));

    string long_string(1000, 'x');
    InsertC(loctestnum, loctesterr, ht, long_string);
    Exists(loctestnum, loctesterr, ht, true, long_string);

    ht.Clear();
    Size(loctestnum, loctesterr, ht, true, 0);
    InsertC(loctestnum, loctesterr, ht, string("reinsert"));
    Exists(loctestnum, loctesterr, ht, true, string("reinsert"));

    InsertC(loctestnum, loctesterr, ht, string("Case"));
    InsertC(loctestnum, loctesterr, ht, string("case"));
    Exists(loctestnum, loctesterr, ht, true, string("Case"));
    Exists(loctestnum, loctesterr, ht, true, string("case"));

    for (int i = 0; i < 10; ++i) {
      InsertC(loctestnum, loctesterr, ht, "str" + to_string(i));
    }
    for (int i = 0; i < 10; ++i) {
      Exists(loctestnum, loctesterr, ht, true, "str" + to_string(i));
    }
    for (int i = 0; i < 10; ++i) {
      Remove(loctestnum, loctesterr, ht, "str" + to_string(i));
      Exists(loctestnum, loctesterr, ht, false, "str" + to_string(i));
    }
    Size(loctestnum, loctesterr, ht, true, 3);

  } catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void MyHashTableString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<string> Test" << endl;
  try {
    lasd::Vector<string> vec(127);
    vec[0] = "@";
    for (uint i = 1; i < 19; i++) {
      vec[i] = vec[i - 1] + static_cast<char>(32 + ((127 * i + 31) % 95));
    }
    for (uint i = 19; i < 127; i++) {
      vec[i] = vec[i - 1];
      vec[i][i % 19] = static_cast<char>(32 + ((127 * i + 31) % 95));
    }

    lasd::HashTableClsAdr<string> htclsadr(101, vec);
    cout << endl << "Begin of HashTableClsAdr<string> Test:" << endl;
    MyHashTableString(htclsadr, vec, loctestnum, loctesterr);
    lasd::HashTableOpnAdr<string> htopnadr(101, vec);
    cout << endl << "Begin of HashTableOpnAdr<string> Test:" << endl;
    MyHashTableString(htopnadr, vec, loctestnum, loctesterr);
    cout << "\n";

    lasd::HashTableClsAdr<string> cophtclsadr(htclsadr);
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    htclsadr = std::move(cophtclsadr);
    NonEqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);
    cophtclsadr = htclsadr;
    EqualHT(loctestnum, loctesterr, cophtclsadr, htclsadr);

    lasd::HashTableOpnAdr<string> cophtopnadr(htopnadr);
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr.Clear();
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    htopnadr = std::move(cophtopnadr);
    NonEqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
    cophtopnadr = htopnadr;
    EqualHT(loctestnum, loctesterr, cophtopnadr, htopnadr);
  } catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of HashTable<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myTestHashTable(uint & testnum, uint & testerr) {
  MyHashTableInt(testnum, testerr);
  MyHashTableDouble(testnum, testerr);
  MyHashTableString(testnum, testerr);
  std::cout << std::endl << "My HashTable Tests (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
