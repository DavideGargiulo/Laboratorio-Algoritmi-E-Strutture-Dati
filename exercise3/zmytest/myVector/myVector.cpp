#include <iostream>
#include <limits>
#include <cmath>

#include "../../container/container.hpp"
#include "../../container/testable.hpp"
#include "../../container/dictionary.hpp"
#include "../../container/traversable.hpp"
#include "../../container/mappable.hpp"
#include "../../container/linear.hpp"

#include "../../vector/vector.hpp"

#include "../../list/list.hpp"

#include "../../zlasdtest/container/container.hpp"
#include "../../zlasdtest/container/testable.hpp"
#include "../../zlasdtest/container/dictionary.hpp"
#include "../../zlasdtest/container/traversable.hpp"
#include "../../zlasdtest/container/mappable.hpp"
#include "../../zlasdtest/container/linear.hpp"

#include "../../zlasdtest/vector/vector.hpp"

#include "../../zlasdtest/list/list.hpp"

using namespace std;

void myVectorInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of My Vector<int> Test:" << endl;
  try {
    // Empty vector tests
    {
      lasd::SortableVector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);
      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);
      Exists(loctestnum, loctesterr, vec, false, 0);
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
    }
    
    // Vector with initial size tests
    {
      lasd::SortableVector<int> vec(3);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 3);
      SetAt(loctestnum, loctesterr, vec, true, 0, 4);
      SetAt(loctestnum, loctesterr, vec, true, 1, 3);
      SetAt(loctestnum, loctesterr, vec, true, 2, 1);
      GetFront(loctestnum, loctesterr, vec, true, 4);
      GetBack(loctestnum, loctesterr, vec, true, 1);
      vec.Sort();
      if (vec[0] == 1 && vec[1] == 3 && vec[2] == 4) {
        loctestnum++;
        cout << loctestnum << "(" << loctesterr << ")" << " " << "Sort test passed!" << endl;
      } else {
        loctestnum++;
        loctesterr++;
        cout << loctestnum << "(" << loctesterr << ")" << " " << "Sort test failed!" << endl;
      }
      lasd::SortableVector<int> vecCopy = vec;
      EqualVector(loctestnum, loctesterr, vecCopy, vec, true);
      lasd::SortableVector<int> vecAssigned;
      vecAssigned = vec;
      EqualVector(loctestnum, loctesterr, vecAssigned, vec, true);
    }

    // Boundary condition tests
    {
      lasd::SortableVector<int> vecLarge(1000000);  // Large but reasonable size
      Empty(loctestnum, loctesterr, vecLarge, false);
      Size(loctestnum, loctesterr, vecLarge, true, 1000000);
    }
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myVectorDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of My Vector<double> Test:" << endl;
  try {
      // Empty vector tests
    {
      lasd::SortableVector<double> vec;
      Empty(loctestnum, loctesterr, vec, true);
      GetFront(loctestnum, loctesterr, vec, false, 0.0);
      GetBack(loctestnum, loctesterr, vec, false, 0.0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0.0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0.0);
      Exists(loctestnum, loctesterr, vec, false, 0.0);
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 0.0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 0.0);
    }
    
    // Vector with initial size tests
    {
      lasd::SortableVector<double> vec(5);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 5);
      SetAt(loctestnum, loctesterr, vec, true, 0, 5.5);
      SetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
      SetAt(loctestnum, loctesterr, vec, true, 2, 1.1);
      SetAt(loctestnum, loctesterr, vec, true, 3, 7.5);
      SetAt(loctestnum, loctesterr, vec, true, 4, 2.5);
      GetFront(loctestnum, loctesterr, vec, true, 5.5);
      GetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
      GetAt(loctestnum, loctesterr, vec, true, 2, 1.1);
      GetAt(loctestnum, loctesterr, vec, true, 3, 7.5);
      GetBack(loctestnum, loctesterr, vec, true, 2.5);
      vec.Sort();
      if (vec[0] == 1.1 && vec[1] == 2.5 && vec[2] == 3.3 && vec[3] == 5.5 && vec[4] == 7.5) {
        loctestnum++;
        cout << loctestnum << "(" << loctesterr << ")" << " " << "Sort test passed!" << endl;
      } else {
        loctestnum++;
        loctesterr++;
        cout << loctestnum << "(" << loctesterr << ")" << " " << "Sort test failed!" << endl;
      }
      lasd::SortableVector<double> vecCopy = vec;
      EqualVector(loctestnum, loctesterr, vecCopy, vec, true);
      lasd::SortableVector<double> vecAssigned;
      vecAssigned = vec;
      EqualVector(loctestnum, loctesterr, vecAssigned, vec, true);
    }

    // Special floating-point value tests
    {
      lasd::SortableVector<double> vec(3);
      SetAt(loctestnum, loctesterr, vec, true, 0, 0.0);
      SetAt(loctestnum, loctesterr, vec, true, 1, std::numeric_limits<double>::infinity());
      SetAt(loctestnum, loctesterr, vec, true, 2, -std::numeric_limits<double>::infinity());

      GetFront(loctestnum, loctesterr, vec, true, 0.0);
      GetAt(loctestnum, loctesterr, vec, true, 1, std::numeric_limits<double>::infinity());
      GetBack(loctestnum, loctesterr, vec, true, -std::numeric_limits<double>::infinity());

      vec.Sort();

      // Check if the sorted order is as expected
      if (vec[0] == -std::numeric_limits<double>::infinity() && vec[1] == 0 && vec[2] == std::numeric_limits<double>::infinity()) {
        loctestnum++;
        cout << loctestnum << "(" << loctesterr << ")" << " " << "Special value sort test passed!" << endl;
      } else {
        loctestnum++;
        loctesterr++;
        cout << loctestnum << "(" << loctesterr << ")" << " " << "Special value sort test failed!" << endl;
      }
    }
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myVectorString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of My Vector<string> Test:" << endl;
  try {
    {
      lasd::SortableVector<double> vec;
      Empty(loctestnum, loctesterr, vec, true);
      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
    }
    
    {
      lasd::SortableVector<string> vec_single(1);
      SetAt(loctestnum, loctesterr, vec_single, true, 0, string("Single"));
      GetFront(loctestnum, loctesterr, vec_single, true, string("Single"));
      GetBack(loctestnum, loctesterr, vec_single, true, string("Single"));
    }

    {
      lasd::SortableVector<string> vec_large(1000);
      Size(loctestnum, loctesterr, vec_large, true, 1000);
    }

    {
      lasd::SortableVector<string> vec_special(3);
      SetAt(loctestnum, loctesterr, vec_special, true, 0, string("New\nLine"));
      SetAt(loctestnum, loctesterr, vec_special, true, 1, string("Tab\tCharacter"));
      SetAt(loctestnum, loctesterr, vec_special, true, 2, string("Unicode\u263A"));
      FoldPreOrder(loctestnum, loctesterr, vec_special, true, &FoldStringConcatenate, string("Special:"), string("Special:New\nLineTab\tCharacterUnicode\u263A"));
    }

    {
      lasd::SortableVector<string> vec_null(2);
      SetAt(loctestnum, loctesterr, vec_null, true, 0, string(""));
      SetAt(loctestnum, loctesterr, vec_null, true, 1, string());
      FoldPreOrder(loctestnum, loctesterr, vec_null, true, &FoldStringConcatenate, string("Empty"), string("Empty"));
    }

    {
      lasd::SortableVector<string> vec_large(1000);
      vec_large.Resize(500);
      Size(loctestnum, loctesterr, vec_large, true, 500);
      vec_large.Resize(1500);
      Size(loctestnum, loctesterr, vec_large, true, 1500);
    }

    {
      lasd::SortableVector<string> vec_special(3);
      SetAt(loctestnum, loctesterr, vec_special, true, 0, string("New\nLine"));
      SetAt(loctestnum, loctesterr, vec_special, true, 1, string("Tab\tCharacter"));
      SetAt(loctestnum, loctesterr, vec_special, true, 2, string("Unicode\u263A"));

      lasd::SortableVector<string> vec_copy(vec_special);
      EqualVector(loctestnum, loctesterr, vec_special, vec_copy, true);
      lasd::SortableVector<string> vec_move(std::move(vec_copy));
      EqualVector(loctestnum, loctesterr, vec_special, vec_move, true);
    }

    {
      lasd::SortableVector<string> vec_sort(3);
      SetAt(loctestnum, loctesterr, vec_sort, true, 0, string("C"));
      SetAt(loctestnum, loctesterr, vec_sort, true, 1, string("B"));
      SetAt(loctestnum, loctesterr, vec_sort, true, 2, string("A"));
      vec_sort.Sort();
      TraversePreOrder(loctestnum, loctesterr, vec_sort, true, &TraversePrint<string>);
    }
  } catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myVector(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  myVectorInt(loctestnum, loctesterr);
  myVectorDouble(loctestnum, loctesterr);
  myVectorString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "Exercise 1A - My Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

void myTestVector(uint & testnum, uint & testerr) {
  myVector(testnum, testerr);
  std::cout << std::endl << "My Vector Tests (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
