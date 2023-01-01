#include "avl.hpp"
#include "bst.hpp"
#include <vector>
#include <chrono>

using namespace std;

template <typename Key, typename Info>
AVLTree<Key, Info> vec2avl(const vector<pair<Key, Info>> &vec)
{
   AVLTree<Key, Info> avl;
   for (auto ele : vec)
      avl.insert(ele.first, ele.second);
   return avl;
}

template <typename Key, typename Info>
BinarySearchTree<Key, Info> vec2bst(const vector<pair<Key, Info>> &vec)
{
   BinarySearchTree<Key, Info> bst;
   for (auto ele : vec)
      bst.insert(ele.first, ele.second);
   return bst;
}

int main()
{
   // TEST 1: default contructor
   {
      AVLTree<int, int> avl;
      BinarySearchTree<int, int> bst;
      if (!(avl.empty() and avl.count() == 0 and avl.height() == -1))
         cerr << "Error in AVLTree: Default Constructor"
              << "\n";
      if (!(bst.empty() and bst.count() == 0 and bst.height() == -1))
         cerr << "Error in BSTree: Default Constructor"
              << "\n";
   }

   // TEST 2: copy contructor and assignment operator
   {
      AVLTree<int, int> avl1 = vec2avl<int, int>({{1, 1}, {2, 2}, {3, 3}, {4, 4}}), avl2(avl1);
      BinarySearchTree<int, int> bst1 = vec2bst<int, int>({{1, 1}, {2, 2}, {3, 3}, {4, 4}}), bst2(bst1);
      avl1.clear();
      bst1.clear();
      if (!(!avl2.empty() and avl2.count() == 4 and avl2.height() == 2))
         cerr << "Error in AVLTree: Copy Constructor"
              << "\n";
      if (!(!bst2.empty() and bst2.count() == 4 and bst2.height() == 3))
         cerr << "Error in BSTree: Copy Constructor"
              << "\n";
   }

   // TEST 3: move contructor
   {
      AVLTree<int, int> avl1 = vec2avl<int, int>({{1, 1}, {2, 2}, {3, 3}, {4, 4}}), avl2(std::move(avl1));
      BinarySearchTree<int, int> bst1 = vec2bst<int, int>({{1, 1}, {2, 2}, {3, 3}, {4, 4}}), bst2(std::move(bst1));
      avl1.clear();
      bst1.clear();
      if (!(!avl2.empty() and avl2.count() == 4 and avl2.height() == 2 and avl1.empty()))
         cerr << "Error in AVLTree: Move Constructor"
              << "\n";
      if (!(!bst2.empty() and bst2.count() == 4 and bst2.height() == 3 and bst1.empty()))
         cerr << "Error in BSTree: Move Constructor"
              << "\n";
   }

   // TEST 4: insert method
   {
      AVLTree<int, int> avl;
      BinarySearchTree<int, int> bst;
      for (int i = 0; i < 10; i++)
      {
         avl.insert(i, i);
         bst.insert(i, i);
      }
      bool res1 = avl.insert(5, 5);
      bool res2 = bst.insert(5, 5);
      if (!(!avl.empty() and avl.count() == 10 and avl.height() == 3 and !res1))
         cerr << "Error in AVLTree: Insert Method"
              << "\n";
      if (!(!bst.empty() and bst.count() == 10 and bst.height() == 9 and !res2))
         cerr << "Error in BSTree: Insert Method"
              << "\n";
   }

   // TEST 5: remove method
   {
      AVLTree<int, int> avl;
      BinarySearchTree<int, int> bst;
      for (int i = 0; i < 10; i++)
      {
         avl.insert(i, i);
         bst.insert(i, i);
      }
      bool res1 = avl.remove(5);
      bool res2 = bst.remove(5);
      if (!(!avl.empty() and avl.count() == 9 and avl.height() == 3 and res1))
         cerr << "Error in AVLTree: Remove Method"
              << "\n";
      if (!(!bst.empty() and bst.count() == 9 and bst.height() == 8 and res2))
         cerr << "Error in BSTree: Remove Method"
              << "\n";
   }

   // TEST 6: find method and operator[]
   {
      AVLTree<int, int> avl;
      BinarySearchTree<int, int> bst;
      for (int i = 0; i < 100; i++)
      {
         avl.insert(i, i);
         avl[i] = i * i;
         bst.insert(i, i);
         bst[i] = i * i;
      }
      for (int i = 0; i < 100; i++)
      {
         if (bst.find(i) != i * i)
            cerr << "Error in find method and operator[] at index " << i
                 << "\n";
      }
   }

   // TEST 7: exists, count, clear and height methods
   {
      AVLTree<int, int> avl;
      BinarySearchTree<int, int> bst;
      for (int i = 0; i < 100; i++)
      {
         avl.insert(i, i);
         bst.insert(i, i);
      }
      for (int i = 0; i < 100; i++)
      {
         if (!bst.exists(i))
            cerr << "Error in exists method"
                 << "\n";
      }
      if (!(avl.height() == 6 and bst.height() == 99))
      {
         cerr << "Error in height method"
              << "\n";
      }
      int before_avl = avl.count();
      int before_bst = bst.count();
      avl.clear();
      bst.clear();
      int after_avl = avl.count();
      int after_bst = bst.count();
      if (!(before_avl == 100 and before_bst == 100 and after_avl == 0 and after_bst == 0))
         cerr << "Error in clear method"
              << "\n";
   }

   /* TEST 8: counter and lisiting functions
   {
      AVLTree<string, int> avl = counter("TheVoyageoftheBeagle.txt");
      if (avl.count() != 12672)
         cerr << "Error in counter function"
              << "\n";
      listing(avl);
   }*/

   // TEST 9: computational complexity
   {
      AVLTree<int, int> avl;
      BinarySearchTree<int, int> bst;
      vector<int>
          size = {1000,
                  10000,
                  100000,
                  1000000,
                  10000000,
                  50000000,
                  100000000,
                  1000000000};

      for (int i : size)
      {
         for (int j = 1; j <= i; j++)
         {
            avl.insert(j, j);
            bst.insert(j, j);
         }
         auto start_avl = chrono::high_resolution_clock::now();
         avl.find(i);
         auto stop_avl = chrono::high_resolution_clock::now();

         auto start_bst = chrono::high_resolution_clock::now();
         bst.find(i);
         auto stop_bst = chrono::high_resolution_clock::now();

         auto duration_avl = chrono::duration_cast<chrono::microseconds>(stop_avl - start_avl);
         auto duration_bst = chrono::duration_cast<chrono::microseconds>(stop_bst - start_bst);

         cout << "Size: " << i << " Time(AVL): " << duration_avl.count() << " Time(BST): " << duration_bst.count() << endl;
      }
   }

   cout << "End of tests";
}
