#include <string>
#include "ring.hpp"

using namespace std;

int main()
{
     // TEST 1 copy constructor
     {
          bi_ring<string, int> br1({{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}});
          bi_ring<string, int> br2(br1);
          if (br1 != br2)
               cerr << "Error in copy constructor\n";
          br1.clear();
          if (br2 != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}}) // deep copy check
               cerr << "Error in copy constructor - deep copy\n";
     }

     // TEST 2 move constructor
     {
          bi_ring<string, int> br1({{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}});
          bi_ring<string, int> br2(move(br1));
          if (br1 == br2)
               cerr << "Error in move constructor\n";
          br1.push_back("bir", 1);
          if (br2 != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}} or
              br1 != bi_ring<string, int>{{"bir", 1}}) // deep copy check
               cerr << "Error in move constructor - deep copy\n";
     }

     // TEST 3 initializer list initialization
     {
          bi_ring<string, int> br({{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}});
          if (br != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}})
               cerr << "Error in initializer list initialization\n";
     }

     // TEST 4 assignment operator
     {
          bi_ring<string, int> br1({{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}}), br2, br3;
          br1 = br1; // self assignment check
          br2 = br1;
          br3 = {{"bir", 1}, {"iki", 2}, {"uc", 3}, {"dort", 4}, {"bes", 5}};
          if (br2 != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}} or
              br3 != bi_ring<string, int>{{"bir", 1}, {"iki", 2}, {"uc", 3}, {"dort", 4}, {"bes", 5}})
               cerr << "Error in assignment operator\n";
     }

     // TEST 5 equal and not equal to operators
     {
          bi_ring<string, int> br1({{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}}), br2;
          br2 = {{"bir", 1}, {"iki", 2}, {"uc", 3}, {"dort", 4}, {"bes", 5}};
          if (br1 != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}} or
              br2 != bi_ring<string, int>{{"bir", 1}, {"iki", 2}, {"uc", 3}, {"dort", 4}, {"bes", 5}} or br1 == br2 or br1 != br1)
               cerr << "Error in equal and not equal to operators\n";
     }

     // TEST 6 push_front method
     {
          bi_ring<string, int> br;
          br.push_front("uno", 1);
          br.push_front("due", 2);
          br.push_front("tre", 3);
          if (br != bi_ring<string, int>{{"tre", 3}, {"due", 2}, {"uno", 1}})
               cerr << "Error in push_front method\n";
     }

     // TEST 7 pop_front method
     {
          bi_ring<string, int> br;
          br.push_front("uno", 1);
          br.push_front("due", 2);
          br.push_front("tre", 3);
          br.pop_front();
          if (br != bi_ring<string, int>{{"due", 2}, {"uno", 1}})
               cerr << "Error in pop_front method\n";
     }

     // TEST 8 push_back method
     {
          bi_ring<string, int> br;
          br.push_back("uno", 1);
          br.push_back("due", 2);
          br.push_back("tre", 3);
          if (br != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}})
               cerr << "Error in push_back method\n";
     }

     // TEST 9 pop_back method
     {
          bi_ring<string, int> br;
          br.push_back("uno", 1);
          br.push_back("due", 2);
          br.push_back("tre", 3);
          br.pop_back();
          if (br != bi_ring<string, int>{{"uno", 1}, {"due", 2}})
               cerr << "Error in pop_back method\n";
     }

     // TEST 10 insert method
     {
          bi_ring<string, int> br;
          br.push_back("uno", 1);
          br.push_back("due", 2);
          br.push_back("quattro", 4);
          br.insert(br.begin() + 2, "tre", 3);
          if (br != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}})
               cerr << "Error in insert method\n";
     }

     // TEST 11 insert_after method
     {
          bi_ring<string, int> br;
          br.push_back("uno", 1);
          br.push_back("due", 2);
          br.push_back("tre", 3);
          br.insert_after(br.begin() + 2, "quattro", 4);
          if (br != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}})
               cerr << "Error in insert_after method\n";
     }

     // TEST 12 erase method
     {
          bi_ring<string, int> br;
          br.push_back("uno", 1);
          br.push_back("due", 2);
          br.push_back("quattro", 4);
          br.push_back("tre", 3);
          br.erase(br.begin() + 2);
          if (br != bi_ring<string, int>{{"uno", 1}, {"due", 2}, {"tre", 3}})
               cerr << "Error in erase method\n";
     }

     // TEST 13 empty method
     {
          bi_ring<string, int> br1, br2;
          br1.push_back("uno", 1);
          br1.push_back("due", 2);
          br1.push_back("tre", 3);
          if (br1.empty() or !br2.empty())
               cerr << "Error in empty method\n";
     }

     // TEST 14 size method
     {
          bi_ring<string, int> br1, br2;
          br1.push_back("uno", 1);
          br1.push_back("due", 2);
          br1.push_back("tre", 3);
          if (br1.size() != 3 or br2.size() != 0)
               cerr << "Error in size method\n";
     }

     // TEST 15 empty method
     {
          bi_ring<string, int> br1, br2;
          br1.push_back("uno", 1);
          br1.push_back("due", 2);
          br1.push_back("tre", 3);
          br1.clear();
          if (br1.size() != 0 or !br1.empty())
               cerr << "Error in clear method\n";
     }

     // TEST 16 shuffle function
     {
          bi_ring<string, int> first, second, result;
          first = {{"uno", 1}, {"due", 2}, {"tre", 3}, {"quattro", 4}};
          second = {{"bir", 1}, {"iki", 2}, {"uc", 3}, {"dort", 4}, {"bes", 5}};
          result = shuffle(first, 1, second, 2, 3);
          if (result != bi_ring<string, int>{{"uno", 1}, {"bir", 1}, {"iki", 2}, {"due", 2}, {"uc", 3}, {"dort", 4}, {"tre", 3}, {"bes", 5}, {"bir", 1}})
               cerr << "Error in shuffle method\n";
     }
     cout << "End of tests\n";
}
