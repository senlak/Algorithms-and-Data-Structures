#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

template <typename Key, typename Info>
class AVLTree
{
     struct Node
     { // node structure
          Key key;
          Info info;
          int height;
          Node *left, *right; // left and right nodes
          Node(const Key &key, const Info &info) : key(key), info(info), height(0), left(nullptr), right(nullptr){};
     } * root; // root node

     void copy(Node *node)
     {
          if (node)
          {
               insert(node->key, node->info);
               copy(node->left);
               copy(node->right);
          }
     }

     void clear(Node *node)
     {
          if (node)
          {
               clear(node->left);
               clear(node->right);
               delete node;
          }
     }

     Node *find(Node *node, const Key &key) const
     {
          if (node)
          {
               if (node->key == key)
                    return node;
               Node *l = find(node->left, key), *r = find(node->right, key);
               return l ? l : r;
          }
          return node;
     }

     // calculate height
     int height(Node *node) const
     {
          if (node)
               return node->height;
          return -1;
     }

     // rotate right
     Node *rotr(Node *y)
     {
          Node *x = y->left;
          Node *T2 = x->right;
          x->right = y;
          y->left = T2;
          y->height = std::max(height(y->left), height(y->right)) + 1;
          x->height = std::max(height(x->left), height(x->right)) + 1;
          return x;
     }

     // rotate left
     Node *lotr(Node *x)
     {
          Node *y = x->right;
          Node *T2 = y->left;
          y->left = x;
          x->right = T2;
          x->height = std::max(height(x->left), height(x->right)) + 1;
          y->height = std::max(height(y->left), height(y->right)) + 1;
          return y;
     }

     // get the balance factor
     int balance_factor(Node *node) const
     {
          if (node)
               return height(node->left) - height(node->right);
          return 0;
     }

     // insert a node
     Node *insert(Node *node, const Key &key, const Info &info)
     {
          // find the correct postion and insert the node
          if (node == nullptr)
               return new Node(key, info);
          if (key < node->key)
               node->left = insert(node->left, key, info);
          else if (key > node->key)
               node->right = insert(node->right, key, info);
          else
               return node;

          // update the balance factor of each node and balance the tree
          node->height = 1 + std::max(height(node->left), height(node->right));
          int b = balance_factor(node);
          if (b > 1)
          {
               if (key < node->left->key)
               {
                    return rotr(node);
               }
               else if (key > node->left->key)
               {
                    node->left = lotr(node->left);
                    return rotr(node);
               }
          }
          if (b < -1)
          {
               if (key > node->right->key)
               {
                    return lotr(node);
               }
               else if (key < node->right->key)
               {
                    node->right = rotr(node->right);
                    return lotr(node);
               }
          }
          return node;
     }

     // delete a node
     Node *remove(Node *root, const Key &key)
     {
          // find the node and delete it
          if (root == nullptr)
               return root;
          if (key < root->key)
               root->left = remove(root->left, key);
          else if (key > root->key)
               root->right = remove(root->right, key);
          else
          {
               if ((root->left == nullptr) ||
                   (root->right == nullptr))
               {
                    Node *temp = root->left ? root->left : root->right;
                    if (temp == nullptr)
                    {
                         temp = root;
                         root = nullptr;
                    }
                    else
                         *root = *temp;
                    delete temp;
               }
               else
               {
                    Node *temp = root->right;
                    while (temp->left != nullptr)
                         temp = temp->left;
                    root->key = temp->key;
                    root->right = remove(root->right, temp->key);
               }
          }

          if (root == nullptr)
               return root;

          // update the balance factor of each node and balance the tree
          root->height = 1 + std::max(height(root->left), height(root->right));
          int b = balance_factor(root);
          if (b > 1)
          {
               if (balance_factor(root->left) >= 0)
               {
                    return rotr(root);
               }
               else
               {
                    root->left = lotr(root->left);
                    return rotr(root);
               }
          }
          if (b < -1)
          {
               if (balance_factor(root->right) <= 0)
               {
                    return lotr(root);
               }
               else
               {
                    root->right = rotr(root->right);
                    return lotr(root);
               }
          }
          return root;
     }

     int count(Node *node) const
     {
          if (node)
               return 1 + count(node->left) + count(node->right);
          return 0;
     }

     // print tree by inorder traversal
     void print_inorder(Node *node) const
     {
          if (node)
          {
               // traverse left node
               print_inorder(node->left);

               // print current node data
               std::cout << "(" << node->key << ", " << node->info
                         << ")"
                         << ",  ";

               // traverse right node
               print_inorder(node->right);
          }
     }

     // print the tree in graphical format
     void print_graph(Node *root, std::string indent, const bool &last) const
     {
          if (root)
          {
               std::cout << indent;
               if (last)
               {
                    std::cout << "R----";
                    indent += "   ";
               }
               else
               {
                    std::cout << "L----";
                    indent += "|  ";
               }
               std::cout << root->key << "\n";
               print_graph(root->left, indent, false);
               print_graph(root->right, indent, true);
          }
     }

     void get_elements(std::vector<std::pair<Key, Info>> &elements, Node *node) const
     {
          if (node)
          {
               get_elements(elements, node->left);

               elements.emplace_back(std::pair<Key, Info>(node->key, node->info));

               get_elements(elements, node->right);
          }
     }

public:
     AVLTree() : root(nullptr){};

     AVLTree(const AVLTree &src)
     {
          root = nullptr;
          if (this != &src)
               copy(src.root);
     }

     AVLTree(AVLTree &&src) : root(src.root) { src.root = nullptr; };

     AVLTree &operator=(const AVLTree &src)
     {
          *this = src;
     }

     ~AVLTree()
     {
          clear();
     }

     bool empty() const
     {
          return root == nullptr;
     }

     bool exists(const Key &key) const
     {
          if (find(root, key))
               return true;
          return false;
     }

     bool insert(const Key &key, const Info &info)
     {
          if (!exists(key))
          {
               root = insert(root, key, info);
               return true;
          }
          return false;
     }

     bool remove(const Key &key)
     {
          if (exists(key))
          {
               root = remove(root, key);
               return true;
          }
          return false;
     }

     Info &find(const Key &key) const
     {
          Node *node = find(root, key);
          if (node)
               return node->info;
          throw "Element with given key does not exist!";
     }

     Info &operator[](const Key &key)
     {
          Node *node = find(root, key);
          if (node)
               return node->info;
          throw "Element with given key does not exist!";
     }

     int count() const
     {
          return count(root);
     }

     int height() const
     {
          return height(root);
     }

     void clear()
     {
          clear(root);
          root = nullptr;
     }

     void print_inorder() const
     {
          print_inorder(root);
     }

     void print_graph() const
     {
          print_graph(root, "", true);
     }

     std::vector<std::pair<Key, Info>> get_elements() const
     {
          std::vector<std::pair<Key, Info>> *elements = new std::vector<std::pair<Key, Info>>;
          get_elements(*elements, root);
          return *elements;
     }
};

AVLTree<std::string, int> &counter(const std::string &fileName)
{
     AVLTree<std::string, int> *dict = new AVLTree<std::string, int>;
     std::ifstream file(fileName);
     std::string word;
     while (file >> word)
     {
          try
          {
               (*dict)[word]++;
          }
          catch (const char *msg)
          {
               if (std::string(msg) == "Element with given key does not exist!")
                    dict->insert(word, 1);
          }
     }
     file.close();
     return *dict;
}

bool compare(std::pair<std::string, int> lhs, std::pair<std::string, int> rhs)
{
     if (lhs.second == rhs.second)
          return lhs.first < rhs.first;
     return lhs.second < rhs.second;
}

void listing(const AVLTree<std::string, int> &src)
{
     auto elements = src.get_elements();
     std::sort(elements.begin(), elements.end(), compare);
     for (auto ele : elements)
          std::cout << ele.first << ": " << ele.second << "\n";
}
