#include <utility>
#include <vector>
#include <string>
#include "sequence.hpp"

//aggregate function
template <typename Info>
Info aggregate(const Info &left, const Info &right)
{
     return left + right;
}

//join function
template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info> &left, const Sequence<Key, Info> &right, Info (*aggregate)(const Info &left, const Info &right))
{
     Sequence<Key, Info> result;

     unsigned int ls = left.size();
     unsigned int rs = right.size();
     bool lft = true;
     if (rs > ls)
     {
          lft = false;
          std::swap(ls, rs);
     }
     for (unsigned int i = 0; i < ls; i++)
     {
          if (i < rs)
          {
               if (left.key_at(i) == right.key_at(i))
               {
                    Info new_info = aggregate(left.info_at(i), right.info_at(i));
                    result.push_back(left.key_at(i), new_info);
               }
               else
               {
                    result.push_back(left.key_at(i), left.info_at(i));
                    result.push_back(right.key_at(i), right.info_at(i));
               }
          }
          else
          {
               if (lft)
               {
                    result.push_back(left.key_at(i), left.info_at(i));
               }
               else
               {
                    result.push_back(right.key_at(i), right.info_at(i));
               }
          }
     }
     return result;
}

//creates a Sequence object from the given vector of pairs and returns it
template <typename Key, typename Info>
Sequence<Key, Info> vec_to_seq(const std::vector<std::pair<Key, Info>> &src)
{
     Sequence<Key, Info> result;
     for (auto element : src)
     {
          result.push_back(element.first, element.second);
     }
     return result;
}

//checks if the given Sequence and vector of pairs are equal(have the same elements in the same order)
template <typename Key, typename Info>
bool equal(const Sequence<Key, Info> &lhs, const std::vector<std::pair<Key, Info>> &rhs)
{
     if (lhs.size() != rhs.size())
     {
          return false;
     }
     unsigned int i = 0;
     for (auto element : rhs)
     {
          if ((lhs.key_at(i) != element.first) or (lhs.info_at(i) != element.second))
          {
               return false;
          }
          i++;
     }

     return true;
}

int main()
{
     //Test 1.1: Default Constructor
     {
          Sequence<int, std::string> s;
          if ((s.size() == 0) and equal(s, {}))
          {
               std::cout << "Test 1.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 1.1 Failed" << std::endl;
          }
     }

     //Test 2.1: Copy Constructor - Empty Source
     {
          Sequence<int, std::string> src;
          Sequence<int, std::string> s(src);
          if ((src.size() == 0) and (s.size() == 0) and (equal(src, {})) and (equal(s, {})) and (s == src) and s.empty())
          {
               std::cout << "Test 2.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 2.1 Failed" << std::endl;
          }
     }

     //Test 2.2: Copy Constructor - Non-Empty Source
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s(src);
          if ((src.size() == 2) and (s.size() == 2) and (equal(src, {{1, "English"}, {2, "Polish"}})) and (equal(s, {{1, "English"}, {2, "Polish"}})) and (src == s))
          {
               std::cout << "Test 2.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 2.2 Failed" << std::endl;
          }
     }

     //Test 2.3: Copy Constructor - Non-Empty Source | Change in Source after copying
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s(src);
          src.clear();
          if ((src.size() == 0) and (s.size() == 2) and (equal(src, {})) and (equal(s, {{1, "English"}, {2, "Polish"}})) and (!(src == s)))
          {
               std::cout << "Test 2.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 2.3 Failed" << std::endl;
          }
     }

     //Test 2.4: Copy Constructor - Non-Empty Source | Change in Object after copying
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s(src);
          s.clear();
          if ((src.size() == 2) and (s.size() == 0) and (equal(s, {})) and (equal(src, {{1, "English"}, {2, "Polish"}})) and !(src == s))
          {
               std::cout << "Test 2.4 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 2.4 Failed" << std::endl;
          }
     }

     //Test 3.1: Assignment Operator - Empty Object and Empty Source
     {
          Sequence<int, std::string> src;
          Sequence<int, std::string> s = src;
          if ((src.size() == 0) and (s.size() == 0) and (equal(src, {})) and (equal(s, {})) and (s == src) and s.empty())
          {
               std::cout << "Test 3.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.1 Failed" << std::endl;
          }
     }

     //Test 3.2: Assignment Operator - Empty Object and Empty Source | Change in Source after copying
     {
          Sequence<int, std::string> src;
          Sequence<int, std::string> s = src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          if ((src.size() == 2) and (s.size() == 0) and (equal(src, {{1, "English"}, {2, "Polish"}})) and (equal(s, {})) and !(s == src))
          {
               std::cout << "Test 3.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.2 Failed" << std::endl;
          }
     }

     //Test 3.3: Assignment Operator - Empty Object and Empty Source | Change in Object after copying
     {
          Sequence<int, std::string> src;
          Sequence<int, std::string> s = src;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          if ((src.size() == 0) and (s.size() == 2) and (equal(s, {{1, "English"}, {2, "Polish"}})) and (equal(src, {})) and !(s == src))
          {
               std::cout << "Test 3.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.3 Failed" << std::endl;
          }
     }

     //Test 3.4: Assignment Operator - Empty Object and Non-Empty Source
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s = src;
          if ((src.size() == 2) and (s.size() == 2) and (equal(src, {{1, "English"}, {2, "Polish"}})) and (equal(s, {{1, "English"}, {2, "Polish"}})) and (src == s))
          {
               std::cout << "Test 3.4 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.4 Failed" << std::endl;
          }
     }

     //Test 3.5: Assignment Operator - Empty Object and Non-Empty Source | Change in Source after copying
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s = src;
          src.clear();
          if ((src.size() == 0) and (s.size() == 2) and (equal(src, {})) and (equal(s, {{1, "English"}, {2, "Polish"}})) and !(src == s))
          {
               std::cout << "Test 3.5 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.5 Failed" << std::endl;
          }
     }

     //Test 3.6: Assignment Operator - Empty Object and Non-Empty Source | Change in Object after copying
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s = src;
          s.clear();
          if ((src.size() == 2) and (s.size() == 0) and (equal(s, {})) and (equal(src, {{1, "English"}, {2, "Polish"}})) and !(src == s))
          {
               std::cout << "Test 3.6 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.6 Failed" << std::endl;
          }
     }

     //Test 3.7: Assignment Operator - Non-Empty Object and Empty Source
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> src;
          s = src;
          if ((src.size() == 0) and (s.size() == 0) and (equal(s, {})) and (equal(src, {}) and (src == s)))
          {
               std::cout << "Test 3.7 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.7 Failed" << std::endl;
          }
     }

     //Test 3.8: Assignment Operator - Non-Empty Object and Empty Source | Change in Source after copying
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> src;
          s = src;
          src = vec_to_seq<int, std::string>({{1, "Japanese"}, {2, "French"}});
          if ((src.size() == 2) and (s.size() == 0) and (equal(s, {})) and (equal(src, {{1, "Japanese"}, {2, "French"}}) and !(src == s)))
          {
               std::cout << "Test 3.8 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.8 Failed" << std::endl;
          }
     }

     //Test 3.9: Assignment Operator - Non-Empty Object and Empty Source | Change in Object after copying
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> src;
          s = src;
          s = vec_to_seq<int, std::string>({{1, "Japanese"}, {2, "French"}});
          if ((src.size() == 0) and (s.size() == 2) and (equal(s, {{1, "Japanese"}, {2, "French"}})) and (equal(src, {}) and !(src == s)))
          {
               std::cout << "Test 3.9 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.9 Failed" << std::endl;
          }
     }

     //Test 3.10: Assignment Operator - Non-Empty Object and Non-Empty Source
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {4, "French"}, {2, "Polish"}});
          s = src;
          if ((src.size() == 2) and (s.size() == 2) and (equal(src, {{1, "English"}, {2, "Polish"}})) and (equal(s, {{1, "English"}, {2, "Polish"}})) and (src == s))
          {
               std::cout << "Test 3.10 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.10 Failed" << std::endl;
          }
     }

     //Test 3.11: Assignment Operator - Non-Empty Object and Non-Empty Source | Change in Source after copying
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {4, "French"}, {2, "Polish"}});
          s = src;
          src.clear();
          if ((src.size() == 0) and (s.size() == 2) and (equal(src, {})) and (equal(s, {{1, "English"}, {2, "Polish"}})) and !(src == s))
          {
               std::cout << "Test 3.11 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.11 Failed" << std::endl;
          }
     }

     //Test 3.12: Assignment Operator - Non-Empty Object and Non-Empty Source | Change in Object after copying
     {
          Sequence<int, std::string> src;
          src = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {4, "French"}, {2, "Polish"}});
          s = src;
          s.clear();
          if ((src.size() == 2) and (s.size() == 0) and (equal(s, {})) and (equal(src, {{1, "English"}, {2, "Polish"}})) and !(src == s))
          {
               std::cout << "Test 3.12 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 3.12 Failed" << std::endl;
          }
     }

     //Test 4.1: Comparison Operator - Empty Source and Object
     {
          Sequence<int, std::string> s, src;
          if (s == src)
          {
               std::cout << "Test 4.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 4.1 Failed" << std::endl;
          }
     }

     //Test 4.2: Comparison Operator - Empty Source and Non-Empty Object
     {
          Sequence<int, std::string> s, src;
          s = vec_to_seq<int, std::string>({{1, "English"}});
          if (!(s == src))
          {
               std::cout << "Test 4.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 4.2 Failed" << std::endl;
          }
     }

     //Test 4.3: Comparison Operator - Non-Empty Source and Empty Object
     {
          Sequence<int, std::string> s, src;
          s = vec_to_seq<int, std::string>({{1, "English"}});
          if (!(s == src))
          {
               std::cout << "Test 4.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 4.3 Failed" << std::endl;
          }
     }

     //Test 4.4: Comparison Operator - Non-Empty Source and Non-Empty Object | Equal
     {
          Sequence<int, std::string> s, src;
          s = vec_to_seq<int, std::string>({{1, "English"}});
          src = vec_to_seq<int, std::string>({{1, "English"}});
          if (s == src)
          {
               std::cout << "Test 4.4 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 4.4 Failed" << std::endl;
          }
     }

     //Test 4.5: Comparison Operator - Non-Empty Source and Non-Empty Object | Not Equal
     {
          Sequence<int, std::string> s, src;
          s = vec_to_seq<int, std::string>({{1, "English"}});
          src = vec_to_seq<int, std::string>({{1, "Polish"}});
          if (!(s == src))
          {
               std::cout << "Test 4.5 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 4.5 Failed" << std::endl;
          }
     }

     //Test 5.1: empty method - Empty Object
     {
          Sequence<int, std::string> s;
          if (s.empty())
          {
               std::cout << "Test 5.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 5.1 Failed" << std::endl;
          }
     }

     //Test 5.2: empty method - Non-Empty Object
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}});
          if (!(s.empty()))
          {
               std::cout << "Test 5.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 5.2 Failed" << std::endl;
          }
     }

     //Test 6.1: size method - Empty Object
     {
          Sequence<int, std::string> s;
          if (s.size() == 0)
          {
               std::cout << "Test 6.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 6.1 Failed" << std::endl;
          }
     }

     //Test 6.2: size method - Non-Empty Object
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {4, "French"}, {2, "Polish"}});
          if (s.size() == 3)
          {
               std::cout << "Test 6.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 6.2 Failed" << std::endl;
          }
     }

     //Test 7.1: push_front method - Empty Object
     {
          Sequence<int, std::string> s;
          s.push_front(3, "Japanese");
          if ((s.size() == 1) and (equal(s, {{3, "Japanese"}})))
          {
               std::cout << "Test 7.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 7.1 Failed" << std::endl;
          }
     }

     //Test 7.2: push_front method - Non-Empty Object
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          s.push_front(3, "Japanese");
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "English"}, {2, "Polish"}})))
          {
               std::cout << "Test 7.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 7.2 Failed" << std::endl;
          }
     }

     //Test 8.1 pop_front method - Empty Object
     {
          Sequence<int, std::string> s;
          bool result = s.pop_front();
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 8.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 8.1 Failed" << std::endl;
          }
     }

     //Test 8.2 pop_front method - Non-Empty Object
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.pop_front();
          if ((s.size() == 2) and (equal(s, {{1, "English"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 8.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 8.2 Failed" << std::endl;
          }
     }

     //Test 9.1: push_back method - Empty Object
     {
          Sequence<int, std::string> s;
          s.push_back(3, "Japanese");
          if ((s.size() == 1) and (equal(s, {{3, "Japanese"}})))
          {
               std::cout << "Test 9.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 9.1 Failed" << std::endl;
          }
     }

     //Test 9.2: push_back method - Non-Empty Object
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          s.push_back(3, "Japanese");
          if ((s.size() == 3) and (equal(s, {{1, "English"}, {2, "Polish"}, {3, "Japanese"}})))
          {
               std::cout << "Test 9.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 9.2 Failed" << std::endl;
          }
     }

     //Test 10.1 pop_back method - Empty Object
     {
          Sequence<int, std::string> s;
          bool result = s.pop_back();
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 10.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 10.1 Failed" << std::endl;
          }
     }

     //Test 10.2 pop_back method - Non-Empty Object
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.pop_front();
          if ((s.size() == 2) and (equal(s, {{1, "English"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 10.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 10.2 Failed" << std::endl;
          }
     }

     //Test 11.1 insert_at_pos method - Empty Object
     {
          Sequence<int, std::string> s;
          bool result = s.insert_at_pos(1, "English", 2);
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 11.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 11.1 Failed" << std::endl;
          }
     }

     //Test 11.2 insert_at_pos method - Non-Empty Object | key does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.insert_at_pos(5, "French", 4);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "English"}, {2, "Polish"}})) and !result)
          {
               std::cout << "Test 11.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 11.2 Failed" << std::endl;
          }
     }

     //Test 11.3 insert_at_pos method - Non-Empty Object | key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.insert_at_pos(5, "French", 1);
          if ((s.size() == 4) and (equal(s, {{3, "Japanese"}, {1, "English"}, {5, "French"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 11.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 11.3 Failed" << std::endl;
          }
     }

     //Test 12.1 insert_at_index method - Empty Object | index = 0
     {
          Sequence<int, std::string> s;
          bool result = s.insert_at_index(1, "English", 0);
          if ((s.size() == 1) and (equal(s, {{1, "English"}})) and result)
          {
               std::cout << "Test 12.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 12.1 Failed" << std::endl;
          }
     }

     //Test 12.2 insert_at_index method - Empty Object | index != 0
     {
          Sequence<int, std::string> s;
          bool result = s.insert_at_index(1, "English", 2);
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 12.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 12.2 Failed" << std::endl;
          }
     }

     //Test 12.3 insert_at_index method - Non-Empty Object | index does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.insert_at_index(1, "English", 4);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "English"}, {2, "Polish"}})) and !result)
          {
               std::cout << "Test 12.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 12.3 Failed" << std::endl;
          }
     }

     //Test 12.4 insert_at_index method - Non-Empty Object | index does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.insert_at_index(1, "French", 1);
          if ((s.size() == 4) and (equal(s, {{3, "Japanese"}, {1, "French"}, {1, "English"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 12.4 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 12.4 Failed" << std::endl;
          }
     }

     //Test 13.1 modify_at_pos method - Empty Object
     {
          Sequence<int, std::string> s;
          bool result = s.modify_at_pos("Spanish", 1);
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 13.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 13.1 Failed" << std::endl;
          }
     }

     //Test 13.2 modify_at_pos method - Non-Empty Object | key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.modify_at_pos("French", 1);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "French"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 13.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 13.2 Failed" << std::endl;
          }
     }

     //Test 13.3 modify_at_pos method - Non-Empty Object | key does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.modify_at_pos("French", 4);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "English"}, {2, "Polish"}})) and !result)
          {
               std::cout << "Test 13.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 13.3 Failed" << std::endl;
          }
     }

     //Test 14.1 modify_at_index method - Empty Object
     {
          Sequence<int, std::string> s;
          bool result = s.modify_at_index("Spanish", 1);
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 14.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 14.1 Failed" << std::endl;
          }
     }

     //Test 14.2 modify_at_index method - Non-Empty Object | index does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.modify_at_index("Spanish", 4);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "English"}, {2, "Polish"}})) and !result)
          {
               std::cout << "Test 14.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 14.2 Failed" << std::endl;
          }
     }

     //Test 14.3 modify_at_index method - Non-Empty Object | index exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.modify_at_index("Spanish", 1);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "Spanish"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 14.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 14.3 Failed" << std::endl;
          }
     }

     //Test 15.1 erase_at_pos method - Empty Object
     {
          Sequence<int, std::string> s;
          bool result = s.erase_at_pos(1);
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 15.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 15.1 Failed" << std::endl;
          }
     }

     //Test 15.2 erase_at_pos method - Non-Empty Object | key does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.erase_at_pos(4);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "English"}, {2, "Polish"}})) and !result)
          {
               std::cout << "Test 15.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 15.2 Failed" << std::endl;
          }
     }

     //Test 15.3 erase_at_pos method - Non-Empty Object | key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.erase_at_pos(3);
          if ((s.size() == 2) and (equal(s, {{1, "English"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 15.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 15.3 Failed" << std::endl;
          }
     }

     //Test 16.1 erase_at_index method - Empty Object
     {
          Sequence<int, std::string> s;
          bool result = s.erase_at_index(1);
          if ((s.size() == 0) and (equal(s, {})) and !result)
          {
               std::cout << "Test 16.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 16.1 Failed" << std::endl;
          }
     }

     //Test 16.2 erase_at_index method - Non-Empty Object | key does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.erase_at_index(4);
          if ((s.size() == 3) and (equal(s, {{3, "Japanese"}, {1, "English"}, {2, "Polish"}})) and !result)
          {
               std::cout << "Test 16.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 16.2 Failed" << std::endl;
          }
     }

     //Test 16.3 erase_at_index method - Non-Empty Object | key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{3, "Japanese"}, {1, "English"}, {2, "Polish"}});
          bool result = s.erase_at_index(1);
          if ((s.size() == 2) and (equal(s, {{3, "Japanese"}, {2, "Polish"}})) and result)
          {
               std::cout << "Test 16.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 16.3 Failed" << std::endl;
          }
     }

     //Test 17.1 swap method - Empty Objects
     {
          Sequence<int, std::string> l, r;
          l.swap(r);
          if ((l.size() == 0) and (r.size() == 0) and (equal(l, {})) and (equal(r, {})) and l == r)
          {
               std::cout << "Test 17.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 17.1 Failed" << std::endl;
          }
     }

     //Test 17.2 swap method - Empty and Non-Empty objects
     {
          Sequence<int, std::string> l, r;
          r = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          l.swap(r);
          if ((l.size() == 2) and (r.size() == 0) and (equal(l, {{1, "English"}, {2, "Polish"}})) and (equal(r, {})) and !(l == r))
          {
               std::cout << "Test 17.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 17.2 Failed" << std::endl;
          }
     }

     //Test 17.3 swap method - Non-Empty objects
     {
          Sequence<int, std::string> l, r;
          l = vec_to_seq<int, std::string>({{1, "Japanese"}});
          r = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          l.swap(r);
          if ((l.size() == 2) and (r.size() == 1) and (equal(l, {{1, "English"}, {2, "Polish"}})) and (equal(r, {{1, "Japanese"}})) and !(l == r))
          {
               std::cout << "Test 17.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 17.3 Failed" << std::endl;
          }
     }

     //Test 17.4 swap method - Non-Empty objects | double swapping
     {
          Sequence<int, std::string> l, r;
          l = vec_to_seq<int, std::string>({{1, "Japanese"}});
          r = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          l.swap(r);
          r.swap(l);
          if ((l.size() == 1) and (r.size() == 2) and (equal(r, {{1, "English"}, {2, "Polish"}})) and (equal(l, {{1, "Japanese"}})) and !(l == r))
          {
               std::cout << "Test 17.4 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 17.4 Failed" << std::endl;
          }
     }

     //Test 17.5 swap method - Non-Empty objects | Change after swapping
     {
          Sequence<int, std::string> l, r;
          l = vec_to_seq<int, std::string>({{1, "Japanese"}});
          r = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          l.swap(r);
          r.clear();
          if ((l.size() == 2) and (r.size() == 0) and (equal(l, {{1, "English"}, {2, "Polish"}})) and (equal(r, {})) and !(l == r))
          {
               std::cout << "Test 17.5 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 17.5 Failed" << std::endl;
          }
     }

     //Test 18.1 clear method - Empty object
     {
          Sequence<int, std::string> s;
          s.clear();
          if ((s.size() == 0) and equal(s, {}) and s.empty())
          {
               std::cout << "Test 18.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 18.1 Failed" << std::endl;
          }
     }

     //Test 18.2 clear method - Non-Empty object
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          s.clear();
          if ((s.size() == 0) and equal(s, {}) and s.empty())
          {
               std::cout << "Test 18.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 18.2 Failed" << std::endl;
          }
     }

     //Test 19.1 get_index method - Empty object
     {
          Sequence<int, std::string> s;
          int result = s.get_index(1);
          if ((s.size() == 0) and equal(s, {}) and s.empty() and (result == -1))
          {
               std::cout << "Test 19.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 19.1 Failed" << std::endl;
          }
     }

     //Test 19.2 get_index method - Non-Empty object | Key does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          int result = s.get_index(3);
          if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty() and (result == -1))
          {
               std::cout << "Test 19.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 19.2 Failed" << std::endl;
          }
     }

     //Test 19.3 get_index method - Non-Empty object | Key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          int result = s.get_index(2);
          if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty() and (result == 1))
          {
               std::cout << "Test 19.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 19.3 Failed" << std::endl;
          }
     }

     //Test 20.1 get method - Empty object
     {
          Sequence<int, std::string> s;
          try
          {
               std::string result = s.get(1);
               std::cout << "Test 20.1 Failed" << std::endl;
          }
          catch (const std::out_of_range &error)
          {
               if ((s.size() == 0) and equal(s, {}) and s.empty())
               {
                    std::cout << "Test 20.1 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 20.1 Failed" << std::endl;
               }
          }
     }

     //Test 20.2 get method - Non-Empty object | Key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          try
          {
               std::string result = s.get(1);
               if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty() and (result == "English"))
               {
                    std::cout << "Test 20.2 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 20.2 Failed" << std::endl;
               }
          }
          catch (const std::out_of_range &error)
          {
               std::cout << "Test 20.2 Failed" << std::endl;
          }
     }

     //Test 20.3 get method - Non-Empty object | Key does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          try
          {
               std::string result = s.get(3);
               std::cout << "Test 20.3 Failed" << std::endl;
          }
          catch (const std::out_of_range &error)
          {
               if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty())
               {
                    std::cout << "Test 20.3 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 20.3 Failed" << std::endl;
               }
          }
     }

     //Test 21.1 key_at method - Empty object
     {
          Sequence<int, std::string> s;
          try
          {
               std::string result = s.get(1);
               std::cout << "Test 21.1 Failed" << std::endl;
          }
          catch (const std::out_of_range &error)
          {
               if ((s.size() == 0) and equal(s, {}) and s.empty())
               {
                    std::cout << "Test 21.1 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 21.1 Failed" << std::endl;
               }
          }
     }

     //Test 21.2 key_at method - Non-Empty object | Index does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          try
          {
               unsigned int key = s.key_at(3);
               std::cout << "Test 21.2 Failed" << key << std::endl;
          }
          catch (const std::out_of_range &error)
          {
               if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty())
               {
                    std::cout << "Test 21.2 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 21.2 Failed" << std::endl;
               }
          }
     }

     //Test 21.3 key_at method - Non-Empty object | Key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          try
          {
               int key = s.key_at(1);
               if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty() and (key == 2))
               {
                    std::cout << "Test 21.3 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 21.3 Failed" << std::endl;
               }
          }
          catch (const std::out_of_range &error)
          {
               std::cout << "Test 21.3 Failed" << std::endl;
          }
     }

     //Test 22.1 info_at method - Empty object
     {
          Sequence<int, std::string> s;
          try
          {
               std::string result = s.info_at(1);
               std::cout << "Test 22.1 Failed" << std::endl;
          }
          catch (const std::out_of_range &error)
          {
               if ((s.size() == 0) and equal(s, {}) and s.empty())
               {
                    std::cout << "Test 22.1 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 22.1 Failed" << std::endl;
               }
          }
     }

     //Test 22.2 info_at method - Non-Empty object | Index does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          try
          {
               std::string result = s.info_at(3);
               std::cout << "Test 21.2 Failed" << std::endl;
          }
          catch (const std::out_of_range &error)
          {
               if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty())
               {
                    std::cout << "Test 22.2 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 22.2 Failed" << std::endl;
               }
          }
     }

     //Test 22.3 info_at method - Non-Empty object | Key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          try
          {
               std::string result = s.info_at(1);
               if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty() and (result == "Polish"))
               {
                    std::cout << "Test 22.3 Passed" << std::endl;
               }
               else
               {
                    std::cout << "Test 22.3 Failed" << std::endl;
               }
          }
          catch (const std::out_of_range &error)
          {
               std::cout << "Test 22.3 Failed" << std::endl;
          }
     }

     //Test 23.1 count method - Empty object
     {
          Sequence<int, std::string> s;
          unsigned int count = s.count(1);
          if ((s.size() == 0) and equal(s, {}) and s.empty() and count == 0)
          {
               std::cout << "Test 23.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 23.1 Failed" << std::endl;
          }
     }

     //Test 23.2 count method - Non-Empty object | key does not exist
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          unsigned int count = s.count(3);
          if ((s.size() == 2) and equal(s, {{1, "English"}, {2, "Polish"}}) and !s.empty() and count == 0)
          {
               std::cout << "Test 23.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 23.2 Failed" << std::endl;
          }
     }

     //Test 23.3 count method - Non-Empty object | key exists
     {
          Sequence<int, std::string> s;
          s = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}, {1, "Spanish"}});
          unsigned int count1 = s.count(1);
          unsigned int count2 = s.count(2);
          if ((s.size() == 3) and equal(s, {{1, "English"}, {2, "Polish"}, {1, "Spanish"}}) and !s.empty() and (count1 == 2) and (count2 == 1))
          {
               std::cout << "Test 23.3 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 23.3 Failed" << std::endl;
          }
     }

     //Test 24.1 join function - Empty objects
     {
          Sequence<int, std::string> left, right, result;
          result = join(left, right, &aggregate);
          if ((result.size() == 0) and equal(result, {}) and result.empty())
          {
               std::cout << "Test 24.1 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 24.1 Failed" << std::endl;
          }
     }

     //Test 24.2 join function - Non-Empty objects | Elements does not have the same key
     {
          Sequence<int, std::string> left, right, result;
          left = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          right = vec_to_seq<int, std::string>({{2, "Japanese"}, {1, "French"}, {4, "Spanish"}});
          result = join(left, right, &aggregate);
          if ((result.size() == 5) and equal(result, {{1, "English"}, {2, "Japanese"}, {2, "Polish"}, {1, "French"}, {4, "Spanish"}}) and !result.empty())
          {
               std::cout << "Test 24.2 Passed" << std::endl;
          }
          else
          {
               std::cout << "Test 24.2 Failed" << std::endl;
          }
     }
     //Test 24.3 join function - Non-Empty objects | First elements have the same key
     {
          Sequence<int, std::string> left, right, result;
          left = vec_to_seq<int, std::string>({{1, "English"}, {2, "Polish"}});
          right = vec_to_seq<int, std::string>({{1, "Japanese"}, {2, "French"}, {4, "Spanish"}});
          result = join(left, right, &aggregate);
          if ((result.size() == 3) and equal(result, {{1, "EnglishJapanese"}, {2, "PolishFrench"}, {4, "Spanish"}}) and !result.empty())
          {
               std::cout << "Test 24.3 Passed" << std::endl;
          }
          else
          {
               result.print();
               std::cout << "Test 24.3 Failed" << std::endl;
          }
     }
}
