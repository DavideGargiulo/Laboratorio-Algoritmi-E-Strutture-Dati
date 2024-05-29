#include <iostream>

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"


#include "../zlasdtest/list/list.hpp"

#include "../zlasdtest/stack/stack.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"

#include "../zlasdtest/queue/queue.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"

#include "../zlasdtest/binarytree/binarytree.hpp"
#include "../zlasdtest/bst/bst.hpp"

/* ************************************************************************** */


using namespace std;

/* ************************************************************************** */

void mytest() {
  unsigned loctestnum = 0, loctesterr = 0;

  lasd::Vector<int> vec(6);
  SetAt(loctestnum, loctesterr, vec, true, 0, 10);
  SetAt(loctestnum, loctesterr, vec, true, 1, 5);
  SetAt(loctestnum, loctesterr, vec, true, 2, 15);
  SetAt(loctestnum, loctesterr, vec, true, 3, 3);
  SetAt(loctestnum, loctesterr, vec, true, 4, 7);

  lasd::BinaryTreeVec<int> btvecInt(vec);
  TraversePostOrder(loctestnum, loctesterr, btvecInt, true, &TraversePrint<int>);
  FoldPostOrder(loctestnum, loctesterr, btvecInt, true, &FoldAdd<int>, 0, 40);
  btvecInt.Root().LeftChild().LeftChild().Element() = 8;
  TraverseInOrder(loctestnum, loctesterr, btvecInt, true, &TraversePrint<int>);
  FoldInOrder(loctestnum, loctesterr, btvecInt, true, &FoldAdd<int>, 0, 45);

  lasd::BinaryTreeLnk<int> btlnkInt(vec);
  TraverseBreadth(loctestnum, loctesterr, btlnkInt, true, &TraversePrint<int>);
  FoldBreadth(loctestnum, loctesterr, btlnkInt, true, &FoldAdd<int>, 0, 40);
  btlnkInt.Root().RightChild().Element() = 12;
  TraversePreOrder(loctestnum, loctesterr, btlnkInt, true, &TraversePrint<int>);
  FoldPreOrder(loctestnum, loctesterr, btlnkInt, true, &FoldAdd<int>, 0, 37);

  btvecInt = move(btlnkInt);
  NonEqualBT(loctestnum, loctesterr, btvecInt, btlnkInt);

  lasd::BST<int> bst;
  bst.Insert(8);
  bst.Insert(3);
  bst.Insert(10);
  bst.Insert(1);
  bst.Insert(6);
  bst.Insert(14);
  bst.Insert(4);
  bst.Insert(7);
  bst.Insert(13);

  Size(loctestnum, loctesterr, bst, true, 9);
  TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

  Min(loctestnum, loctesterr, bst, true, 1);
  Max(loctestnum, loctesterr, bst, true, 14);

  Remove(loctestnum, loctesterr, bst, true, 10);
  TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

  Size(loctestnum, loctesterr, bst, true, 8);

  Min(loctestnum, loctesterr, bst, true, 1);
  Max(loctestnum, loctesterr, bst, true, 14);

  lasd::BST<int> bst2;
  bst2.Insert(5);
  bst2.Insert(3);
  bst2.Insert(8);
  bst2.Insert(1);
  bst2.Insert(4);
  bst2.Insert(7);
  bst2.Insert(10);

  NonEqualBST(loctestnum, loctesterr, bst, bst2);
  bst2 = move(bst);
  NonEqualBST(loctestnum, loctesterr, bst, bst2);

  cout << endl << "My Test " << ((loctesterr == 0) ? "0 errors" : to_string(loctesterr) + " errors") << " out of " << loctestnum << " tests" << endl;
}