#include <stdexcept>
#include <iostream>
#include <utility>

template <typename Key, typename Info>
class bi_ring // bi-directionally linked ring
{
public:
     struct Element // Element struct
     {
          Element(Key key, Info info)
          {
               this->key = key;
               this->info = info;
          };
          Key key;
          Info info;
     };

private:
     struct Node // Node structure
     {
          Node(Key key, Info info, Node *prev = nullptr, Node *next = nullptr)
          {
               element = new Element(key, info);
               this->prev = prev;
               this->next = next;
          }
          Element *element;
          Node *prev;
          Node *next;
     };
     Node *head;       // head
     Node *tail;       // tail
     unsigned int len; // size

public:
     class iterator // iterator
     {
          Node *node; // current node

     public:
          friend class bi_ring;
          iterator(Node *node = nullptr) // constructor
          {
               this->node = node;
          }
          iterator &operator=(const iterator &src) // assignment operator
          {
               node = src.node;
               return *this;
          }
          iterator &operator=(const Node *src) // assignment operator node
          {
               node = src.node;
               return *this;
          }
          bool operator==(const iterator &rhs) const // equal to operator
          {
               return node == rhs.node;
          }
          bool operator==(const Node *rhs) const // equal to operator node
          {
               return node == rhs;
          }
          bool operator!=(const iterator &rhs) const // not equal to operator
          {
               return node != rhs.node;
          }
          bool operator!=(const Node *rhs) const // not equal to operator node
          {
               return node != rhs;
          }
          iterator &operator++() // prefix increment operator
          {
               if (node)
                    node = node->next;
               return *this;
          }
          iterator operator++(int) // postfix increment operator
          {
               iterator it = *this;
               ++*this;
               return it;
          }
          iterator &operator--() // prefix decrement operator
          {
               if (node)
                    node = node->prev;
               return *this;
          }
          iterator operator--(int) // postfix decrement operator
          {
               {
                    iterator it = *this;
                    --*this;
                    return it;
               }
          }
          iterator operator+(int pos) // addition operator
          {
               if (pos < 0)
                    return (*this - (-pos));
               iterator it(node);
               while (pos)
               {
                    it++;
                    pos--;
               }
               return it;
          }
          iterator operator-(int pos) // subtraction operator
          {
               if (pos < 0)
                    return (*this + (-pos));
               iterator it(node);
               while (pos)
               {
                    it--;
                    pos--;
               }
               return it;
          }

          iterator &operator+=(int pos) // plus equal to operator
          {
               *this = *this + pos;
               return *this;
          }
          iterator &operator-=(int pos) // minus equal to operator
          {
               *this = *this - pos;
               return *this;
          }

          Element &operator*() // dereference operator
          {
               if (node)
                    return *(node->element);
               throw std::runtime_error("Iterator points to nullptr");
          }
          Element *operator->() // arrow operator
          {
               if (node)
                    return node->element;
               throw std::runtime_error("Iterator points to nullptr");
          }
     };
     // constant iterator
     class const_iterator
     {
     private:
          Node *node; // current node of the const_iterator

     public:
          friend class bi_ring;
          const_iterator(Node *node = nullptr) // constructor
          {
               this->node = node;
          }
          const_iterator &operator=(const const_iterator &src) // assignment operator
          {
               node = src.node;
               return *this;
          }
          const_iterator &operator=(const Node *src) // assignment operator node
          {
               node = src.node;
               return *this;
          }
          bool operator==(const const_iterator &rhs) const // equal to operator
          {
               return node == rhs.node;
          }
          bool operator==(const Node *rhs) const // equal to operator node
          {
               return node == rhs;
          }
          bool operator!=(const const_iterator &rhs) const // not equal to operator
          {
               return node != rhs.node;
          }
          bool operator!=(const Node *rhs) const // not equal to operator node
          {
               return node != rhs;
          }
          const_iterator &operator++() // prefix increment operator
          {
               if (node)
                    node = node->next;
               return *this;
          }
          const_iterator operator++(int) // postfix increment operator
          {
               const_iterator it = *this;
               ++*this;
               return it;
          }
          const_iterator &operator--() // prefix decrement operator
          {
               if (node)
                    node = node->prev;
               return *this;
          }
          const_iterator operator--(int) // postfix decrement operator
          {
               {
                    const_iterator it = *this;
                    --*this;
                    return it;
               }
          }
          const_iterator operator+(int pos) // addition operator
          {
               if (pos < 0)
                    return (*this - (-pos));
               const_iterator it(node);
               while (pos)
               {
                    it++;
                    pos--;
               }
               return it;
          }
          const_iterator operator-(int pos) // subtraction operator
          {
               if (pos < 0)
                    return (*this + (-pos));
               const_iterator it(node);
               while (pos)
               {
                    it--;
                    pos--;
               }
               return it;
          }

          const_iterator &operator+=(int pos) // plus equal to operator
          {
               *this = *this + pos;
               return *this;
          }
          const_iterator &operator-=(int pos) // minus equal to operator
          {
               *this = *this - pos;
               return *this;
          }

          const Element &operator*() const // dereference operator
          {
               if (node)
                    return *(node->element);
               throw std::runtime_error("Iterator points to nullptr");
          }
          Element *operator->() const // arrow operator
          {
               if (node)
                    return node->element;
               throw std::runtime_error("Iterator points to nullptr");
          }
     };
     bi_ring() // constructor
     {
          head = nullptr;
          tail = nullptr;
          len = 0;
     }
     bi_ring(const bi_ring &src) // copy constructor
     {
          head = nullptr;
          tail = nullptr;
          len = 0;
          *this = src;
     }
     bi_ring(bi_ring &&src) // move constructor
     {
          head = nullptr;
          tail = nullptr;
          len = 0;
          std::swap(head, src.head);
          std::swap(tail, src.tail);
          std::swap(len, src.len);
     }
     bi_ring(const std::initializer_list<std::pair<Key, Info>> &src) // initializer list constructor
     {
          head = nullptr;
          tail = nullptr;
          len = 0;
          *this = src;
     }
     ~bi_ring() // destructor
     {
          clear();
     }
     bi_ring &operator=(const bi_ring &src) // assignment operator
     {
          if (this == &src)
               return *this;
          clear();
          auto cit = src.cbegin();
          for (unsigned int i = 0; i < src.size(); i++, cit++)
               push_back(cit->key, cit->info);

          return *this;
     }
     bi_ring &operator=(const std::initializer_list<std::pair<Key, Info>> &src) // assignment operator initializer list
     {
          clear();
          auto sit = src.begin();
          for (unsigned int i = 0; i < src.size(); i++, sit++)
               push_back(sit->first, sit->second);
          return *this;
     }
     bool operator==(const bi_ring &src) // equal to operator
     {
          if (len != src.len)
               return false;
          auto cit = cbegin();
          auto scit = src.cbegin();
          for (unsigned int i = 0; i < len; i++, cit++, scit++)
               if (cit->key != scit->key or cit->info != scit->info)
                    return false;
          return true;
     }
     bool operator!=(const bi_ring &src) // not equal to operator
     {
          return !(*this == src);
     }
     iterator push_front(const Key &key, const Info &info) // adds element with given key and info to the front and returns iterator to the element added
     {
          return insert(begin(), key, info);
     }
     iterator pop_front() // removes element from the front and returns iterator to the first element
     {
          return erase(begin());
     }
     iterator push_back(const Key &key, const Info &info) // adds element with given key and info to the back and returns iterator to the element added
     {
          return insert_after(end(), key, info);
     }
     iterator pop_back() // removes element from the front and returns iterator to the last element
     {
          return erase(end());
     }
     iterator insert(iterator position, const Key &key, const Info &info) // adds element with given key and info before the given position and returns iterator to the element added
     {
          if (position.node)
          {
               Node *prev = position.node->prev;
               Node *new_ele = new Node(key, info, prev, position.node);
               prev->next = new_ele;
               position.node->prev = new_ele;
               len++;
               if (position.node == head)
                    head = new_ele;
               if (position.node == tail)
                    tail = new_ele;
               return iterator(new_ele);
          }
          if (position.node == head)
          {
               head = new Node(key, info);
               head->next = head;
               head->prev = head;
               tail = head;
               len++;
               return begin();
          }
          return position;
     }
     iterator insert_after(iterator position, const Key &key, const Info &info) // adds element with given key and info after the given position and returns iterator to the element added
     {
          if (position.node)
          {
               Node *next = position.node->next;
               Node *new_ele = new Node(key, info, position.node, next);
               next->prev = new_ele;
               position.node->next = new_ele;
               len++;
               if (position.node == tail)
                    tail = new_ele;
               return iterator(new_ele);
          }
          if (position.node == head)
          {
               head = new Node(key, info);
               head->next = head;
               head->prev = head;
               tail = head;
               len++;
               return begin();
          }
          return position;
     }
     iterator erase(iterator position) // removes element at the given position and returns iterator to the element in the place of the removed element
     {
          if (position.node)
          {
               Node *prev = position.node->prev;
               Node *next = position.node->next;
               if (position.node == next)
               {
                    delete head;
                    head = nullptr;
                    tail = head;
                    len = 0;
                    return begin();
               }
               delete position.node;
               prev->next = next;
               next->prev = prev;
               len--;
               if (position.node == head)
                    head = next;
               if (position.node == tail)
                    tail = next;
               return iterator(next);
          }
          return iterator(nullptr);
     }
     bool empty() const // returns true if the bi_ring is empty else returns false
     {
          return head == nullptr;
     }
     unsigned int size() const // returns the number of elements in the bi_ring
     {
          return len;
     }
     void clear() // removes all the elements of the bi_ring
     {
          while (!empty())
               pop_front();
     }
     void print() const // displays all the elements of the bi_ring
     {
          auto it = cbegin();
          for (unsigned int i = 0; i < len; i++, it++)
               std::cout << it->key << ": " << it->info << "\n";
     }
     iterator begin() const // returns an iterator to the first element
     {
          return iterator(head);
     }
     iterator end() const // returns an iterator to the last element
     {
          return iterator(tail);
     }
     const_iterator cbegin() const // returns an const_iterator to the first element
     {
          return const_iterator(head);
     }
     const_iterator cend() const // returns an const_iterator to the last element
     {
          return const_iterator(tail);
     }
};

template <typename Key, typename Info>
bi_ring<Key, Info> shuffle(const bi_ring<Key, Info> &first, unsigned int fcnt, const bi_ring<Key, Info> &second, unsigned int scnt, unsigned int reps)
{
     bi_ring<Key, Info> result;
     if (first.empty())
          fcnt = 0;
     if (second.empty())
          scnt = 0;
     if (fcnt == 0 and scnt == 0)
          reps = 0;
     auto fit = first.cbegin();
     auto sit = second.cbegin();
     for (int i = 0; i < reps; i++)
     {
          for (int j = 0; j < fcnt; j++, fit++)
               result.push_back(fit->key, fit->info);
          for (int k = 0; k < scnt; k++, sit++)
               result.push_back(sit->key, sit->info);
     }

     return result;
}